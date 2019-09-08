// Copyright (c) 2016 Josh Blum
//               2019 Nicholas Corgan
// SPDX-License-Identifier: BSL-1.0

#include <Pothos/Config.hpp>
#include <Poco/Logger.h>

class PothosJavaLogger
{
public:
    PothosJavaLogger(const std::string &name):
        _logger(Poco::Logger::get(name))
    {
        return;
    }

    void log(const std::string &source, const std::string &text, const std::string &level)
    {
        _logger.log(Poco::Message(source, text, levelToPrio(level)));
    }

private:

    static Poco::Message::Priority levelToPrio(const std::string &level)
    {
        if (level == "FATAL") return Poco::Message::PRIO_FATAL;
        if (level == "CRITICAL") return Poco::Message::PRIO_CRITICAL;
        if (level == "ERROR") return Poco::Message::PRIO_ERROR;
        if (level == "WARNING") return Poco::Message::PRIO_WARNING;
        if (level == "INFO") return Poco::Message::PRIO_INFORMATION;
        if (level == "DEBUG") return Poco::Message::PRIO_DEBUG;
        return Poco::Message::PRIO_INFORMATION;
    }

    Poco::Logger &_logger;
};

#include <Pothos/Managed.hpp>

static auto managedPothosJavaLogger = Pothos::ManagedClass()
    .registerConstructor<PothosJavaLogger, std::string>()
    .registerMethod(POTHOS_FCN_TUPLE(PothosJavaLogger, log))
    .commit("Pothos/Java/Logger");
