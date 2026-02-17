#pragma once

#include "UnlabeledUndirectedGraph/UnlabeledUndirectedGraph1.hpp"
#ifdef _DEBUG
// Compiling in Debug configuration
// Use UnlabeledUndirectedGraph1 wrapped by its checking component
#include "UnlabeledUndirectedGraph/UnlabeledUndirectedGraphChecking.hpp"
typedef UnlabeledUndirectedGraphChecking1< UnlabeledUndirectedGraph1> UnlabeledUndirectedGraph;
#else
// Compiling in Release configuration
// Use UnlabeledUndirectedGraph1 without any "protection" from a checking component
typedef UnlabeledUndirectedGraph1 UnlabeledUndirectedGraph;
#endif
