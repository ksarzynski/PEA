#pragma once

enum algorithmEnum {
	BRUTE_FORCE = 0,
	DYNAMIC = 1,
	BRANCH_AND_BOUND = 2,
	SIMULATED_ANNEALING = 3,
	TABOO_SEARCH = 4
};

enum nextSolutionMethod {
	SWAP = 0,
	INVERT = 1,
	INSERT = 2
};

enum coolingMethod {
	GEOMETRICAL = 0,
	CAUCHY = 1
};

enum firstSolutionMethod {
	RANDOM = 0,
	GREEDY = 1
};