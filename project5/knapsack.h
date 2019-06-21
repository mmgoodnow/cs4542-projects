// Knapsack class
// Michael Goodnow
// based on starter code

class knapsack {
  public:
	knapsack(ifstream &fin);
	knapsack(const knapsack &);
	knapsack(const knapsack &, int);
	knapsack();
	int getCost(int) const;
	int getValue(int) const;
	int getCost() const;
	int getValue() const;
	bool isLegal() const;
	int getNumDecided() const;
	float valueCostRatio(int) const;
	int getNumObjects() const;
	int getCostLimit() const;
	void printSolution();
	void select(int);
	void deselect(int);
	bool isSelected(int) const;
	float getBound() const;
	knapsack neighbor(int, int);

  private:
	int numDecided;
	int numObjects;
	int costLimit;
	vector<int> value;
	vector<int> cost;
	vector<bool> selected;
	int totalValue;
	int totalCost;
	float calcBound() const;
	int bound;
};

// Sort comparator that will take a pair of knapsack object id and float which
// is the ratio of totalValue to weight
struct compare_knapsack_objects {
	bool operator()(pair<int, float> &a, pair<int, float> &b) {
		return a.second > b.second;
	}
};

// Comparator that will take a pair of knapsacks and compare their bounds.
// Returns true if the first bound is bigger than the second bound.
struct compare_bound {
	bool operator()(knapsack &a, knapsack &b) {
		return a.getBound() > b.getBound();
	}
};

// Construct a new knapsack instance using the data in fin.
knapsack::knapsack(ifstream &fin) {
	int n, b, j, v, c;

	fin >> n; // read the number of objects
	fin >> b; // read the cost limit

	numObjects = n;
	costLimit = b;

	value.resize(n);
	cost.resize(n);
	selected.resize(n);

	for (int i = 0; i < n; i++) {
		fin >> j >> v >> c;
		value[j] = v;
		cost[j] = c;
		deselect(j);
	}

	totalValue = 0;
	totalCost = 0;
	numDecided = 0;
	bound = calcBound();
}

// Knapsack copy constructor.
knapsack::knapsack(const knapsack &k) {
	int n = k.getNumObjects();

	value.resize(n);
	cost.resize(n);
	selected.resize(n);
	numObjects = k.getNumObjects();
	costLimit = k.getCostLimit();
	numDecided = k.getNumDecided();

	totalCost = 0;
	totalValue = 0;

	for (int i = 0; i < n; i++) {
		value[i] = k.getValue(i);
		cost[i] = k.getCost(i);
		if (k.isSelected(i))
			select(i);
		else
			deselect(i);
	}

	bound = calcBound();
}

// subproblem constructor
knapsack::knapsack(const knapsack &k, int numDecided) {
	int n = k.getNumObjects();

	this->numDecided = numDecided;

	value.resize(n);
	cost.resize(n);
	selected.resize(n);
	numObjects = k.getNumObjects();
	costLimit = k.getCostLimit();

	totalCost = 0;
	totalValue = 0;

	for (int i = 0; i < n; i++) {
		value[i] = k.getValue(i);
		cost[i] = k.getCost(i);
		deselect(i);
	}

	for (int i = 0; i < numDecided; ++i) {
		if (k.isSelected(i)) select(i);
	}
	bound = calcBound();
}

// default constructor
knapsack::knapsack() {}

int knapsack::getNumObjects() const { return numObjects; }

int knapsack::getCostLimit() const { return costLimit; }

// Return the value of the ith object.
int knapsack::getValue(int i) const { return value[i]; }

// Return the cost of the ith object.
int knapsack::getCost(int i) const { return cost[i]; }

// Return the cost of the selected objects.
int knapsack::getCost() const { return totalCost; }

// Return the value of the selected objects.
int knapsack::getValue() const { return totalValue; }

bool knapsack::isLegal() const { return totalCost <= costLimit; }

// Return the number of decided objects.
int knapsack::getNumDecided() const { return this->numDecided; }

float knapsack::valueCostRatio(int i) const {
	return (float)this->getValue(i) / (float)this->getCost(i);
}

// Print all information about the knapsack.
ostream &operator<<(ostream &ostr, const knapsack &k) {
	ostr << "------------------------------------------------" << endl;
	ostr << "Num objects: " << k.getNumObjects()
	     << " Cost Limit: " << k.getCostLimit() << endl;

	int totalValue = 0;
	int totalCost = 0;

	for (int i = 0; i < k.getNumObjects(); i++) {
		totalValue += k.getValue(i);
		totalCost += k.getCost(i);
	}

	cout << "Total value: " << totalValue << endl;
	cout << "Total cost: " << totalCost << endl << endl;

	for (int i = 0; i < k.getNumObjects(); i++)
		cout << i << "  " << k.getValue(i) << " " << k.getCost(i) << endl;

	cout << endl;

	return ostr;
}

// Prints out the solution.
void knapsack::printSolution() {
	cout << "------------------------------------------------" << endl;

	cout << "Decided values: " << getNumDecided() << endl;
	cout << "Bound: " << getBound() << endl;
	cout << "Total value: " << getValue() << endl;
	cout << "Total cost: " << getCost() << endl << endl;

	// Print out objects in the solution
	for (int i = 0; i < getNumObjects(); i++)
		if (isSelected(i))
			cout << i << "  " << getValue(i) << " " << getCost(i) << endl;

	cout << endl;
}

// Overloaded output operator for vectors.
ostream &operator<<(ostream &ostr, vector<bool> v) {
	for (int i = 0; i < v.size(); i++)
		cout << v[i] << endl;

	return ostr;
}

// Select object i.
void knapsack::select(int i) {
	if (selected[i] == false) {
		selected[i] = true;
		totalCost = totalCost + getCost(i);
		totalValue = totalValue + getValue(i);
	}
}

// deselect object i.
void knapsack::deselect(int i) {
	if (selected[i] == true) {
		selected[i] = false;
		totalCost = totalCost - getCost(i);
		totalValue = totalValue - getValue(i);
	}
}

// Return true if object i is currently selected, and false otherwise.
bool knapsack::isSelected(int i) const { return selected[i]; }

// Find an upper bound on the value of this knapsack with the items
// from 0 to numDecided taken as decided
float knapsack::calcBound() const {
	vector<pair<int, float>> vec;
	for (int i = this->numDecided; i < this->getNumObjects(); i++) {
		pair<int, float> p(i, this->valueCostRatio(i));
		vec.push_back(p);
	}

	sort(vec.begin(), vec.end(), compare_knapsack_objects());

	int space_remaining = this->getCostLimit() - this->getCost();
	int totalValue = this->getValue();

	// calculate bound for the undecided objects
	for (int i = 0; i < vec.size(); i++) {
		int obj = vec[i].first;
		if (this->getCost(obj) <= space_remaining) {
			space_remaining -= this->getCost(obj);
			totalValue += this->getValue(obj);
			if (space_remaining == 0) return totalValue;
		} else if (space_remaining > 0) {
			double fraction = (float)space_remaining / this->getCost(obj);
			return fraction * this->getValue(obj) + totalValue;
		}
	}

	return (float)totalValue;
}

float knapsack::getBound() const { return bound; }

knapsack knapsack::neighbor(int i, int j) const {
	knapsack k(this);

	if (isSelected(i)) {
		k.deselect(i);
	} else {
		k.select(i);
	}

	if (isSelected(j)) {
		k.deselect(j);
	} else {
		k.select(j);
	}
	return k;
}

knapsack knapsack::bestNeighbor() const {
	knapsack best;
	for (int i = 0; i < getNumObjects(); ++i) {
		for (int j = 0; j < getNumObjects(); ++j) {
			if (i >= j) continue;
			knapsack cur = neighbor(i, j);
			if (cur.getValue() > getValue()) {
				best = cur;
			}
		}
	}
	return best;
}