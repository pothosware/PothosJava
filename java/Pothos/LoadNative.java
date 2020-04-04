// Copyright (c) 2020 Nicholas Corgan
// SPDX-License-Identifier: BSL-1.0

package Pothos;

public class LoadNative
{
    public static void loadNative()
    {
        try
        {
            // Note: this becomes a nop if the library is already loaded.
            System.loadLibrary("JavaSupport");
        }
        catch(java.lang.UnsatisfiedLinkError e)
        {
            System.err.println("Failed to load JNI functions for Pothos Java support.");
        }
    }
}
