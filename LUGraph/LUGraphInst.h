#pragma once

#include "LabeledUndirectedGraph/LabeledUndirectedGraph1.hpp"
#ifdef _DEBUG
// Compiling in Debug configuration
// Use UnlabeledUndirectedGraph1 wrapped by its checking component
#include "LabeledUndirectedGraph/LabeledUndirectedGraphChecking1.hpp"
typedef LabeledUndirectedGraphChecking1< LabeledUndirectedGraph1> UnlabeledUndirectedGraph;
#else
// Compiling in Release configuration
// Use UnlabeledUndirectedGraph1 without any "protection" from a checking component
typedef LabeledUndirectedGraph1 UnlabeledUndirectedGraph;
#endif
