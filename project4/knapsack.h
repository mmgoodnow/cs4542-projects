// Knapsack class
// Michael Goodnow
// based on starter code

class knapsack {
  public:
	knapsack(ifstream &fin);
	knapsack(const knapsack &);
	knapsack();
	int getCost(int) const;
	int getValue(int) const;
	int getCost() const;
	int getValue() const;
	float valueCostRatio(int) const;
	int getNumObjects() const;
	int getCostLimit() const;
	void printSolution();
	void select(int);
	void deselect(int);
	bool isSelected(int) const;
	float bound() const;

  private:
	int numObjects;
	int costLimit;
	vector<int> value;
	vector<int> cost;
	vector<bool> selected;
	int totalValue;
	int totalCost;
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
}

// Knapsack copy constructor.
knapsack::knapsack(const knapsack &k) {
	int n = k.getNumObjects();

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
		if (k.isSelected(i))
			select(i);
		else
			deselect(i);
	}
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

float knapsack::bound() const {
	vector<pair<int, float>> vec;
	for (int i = 0; i < this->getNumObjects(); i++) {
		pair<int, float> p(i, this->valueCostRatio(i));
		vec.push_back(p);
	}
	sort(vec.begin(), vec.end(), compare_knapsack_objects());

	int weight_remaining = this->getCostLimit();
	int value = 0;
	for (int i = 0; i < vec.size(); i++) {
		int obj = vec[i].first;
		if (this->getCost(obj) <= weight_remaining) {
			weight_remaining -= this->getCost(obj);
			value += this->getValue(obj);
			if (weight_remaining == 0) return value;
		} else if (weight_remaining > 0) {
			double fraction = (float)weight_remaining / this->getCost(obj);
			weight_remaining = 0;
			return fraction * this->getValue(obj) + value;
		}
	}

	return (float) value;
}