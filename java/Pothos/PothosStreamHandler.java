// Copyright (c) 2019-2020 Nicholas Corgan
// SPDX-License-Identifier: BSL-1.0

package Pothos;

import java.util.logging.Formatter;
import java.util.logging.Level;
import java.util.logging.LogRecord;
import java.util.logging.SimpleFormatter;
import java.util.logging.StreamHandler;

public class PothosStreamHandler extends StreamHandler
{
    static
    {
        LoadNative.loadNative();
    }

    private static Proxy ManagedLoggerClass = new ProxyEnvironment("managed")
                                                      .findProxy("Pothos/Java/Logger");

    private Proxy managedLoggerProxy = null;

    public PothosStreamHandler(String name)
    {
        super();

        managedLoggerProxy = ManagedLoggerClass.call("()", name);
    }

    private boolean isLevelGreaterOrEqual(Level level1, Level level2)
    {
        return (level1.intValue() >= level2.intValue());
    }

    @Override
    public void publish(LogRecord record)
    {
        String level = null;
        if(isLevelGreaterOrEqual(record.getLevel(), Level.SEVERE))
        {
            level = "CRITICAL";
        }
        else if(isLevelGreaterOrEqual(record.getLevel(), Level.WARNING))
        {
            level = "WARNING";
        }
        else if(isLevelGreaterOrEqual(record.getLevel(), Level.INFO))
        {
            level = "INFO";
        }
        else
        {
            level = "DEBUG";
        }

        Formatter formatter = this.getFormatter();
        if(null == formatter)
        {
            formatter = new SimpleFormatter();
        }
        String message = formatter.format(record);

        Object[] logArgs = new Object[3];
        logArgs[0] = "Java";
        logArgs[1] = message;
        logArgs[2] = level;
        managedLoggerProxy.call("log", logArgs);
    }
}
