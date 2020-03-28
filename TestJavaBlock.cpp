// Copyright (c) 2019 Nicholas Corgan
// SPDX-License-Identifier: BSL-1.0

#include <Pothos/Testing.hpp>
#include <Pothos/Framework.hpp>
#include <Pothos/Proxy.hpp>

#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream>

POTHOS_TEST_BLOCK("/proxy/java/tests", java_module_import)
{
    auto env = Pothos::ProxyEnvironment::make("java");
    auto proxy = env->findProxy("Pothos.Proxy");
}
