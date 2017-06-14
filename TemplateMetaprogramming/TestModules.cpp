#if 0

import std.core;

void useModules() {
	using namespace std;
	vector<string> v{ "Plato", "Descartes", "Bacon" };
	copy(v.begin(), v.end(), ostream_iterator<string>(cout, "\n"));
}

#endif
