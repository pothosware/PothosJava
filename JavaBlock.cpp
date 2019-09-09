// Copyright (c) 2014-2016 Josh Blum
//                    2019 Nicholas Corgan
// SPDX-License-Identifier: BSL-1.0

#include <Pothos/Framework.hpp>
#include <Pothos/Managed.hpp>
#include <Pothos/Proxy.hpp>

class JavaBlock : Pothos::Block
{
public:
    JavaBlock(void)
    {
        this->registerCall(this, POTHOS_FCN_TUPLE(JavaBlock, _setJavaBlock));
    }

    static Block *make(void)
    {
        return new JavaBlock();
    }

    void _setJavaBlock(const Pothos::Proxy &block)
    {
        _block = block;
    }

    void work(void)
    {
        _block.call("work");
    }

    void activate(void)
    {
        _block.call("activate");
    }

    void deactivate(void)
    {
        _block.call("deactivate");
    }

    void propagateLabels(const Pothos::InputPort *input, const Pothos::LabelIteratorRange &labels)
    {
        _block.call("propagateLabelsAdaptor", input, labels);
    }

    Pothos::Object opaqueCallHandler(const std::string &name, const Pothos::Object *inputArgs, const size_t numArgs)
    {
        if (name == "_setJavaBlock") return Pothos::Block::opaqueCallHandler(name, inputArgs, numArgs);
        if (not _block) throw name;
        auto env = _block.getEnvironment();
        Pothos::ProxyVector args(numArgs);
        for (size_t i = 0; i < numArgs; i++)
        {
            args[i] = env->convertObjectToProxy(inputArgs[i]);
        }
        auto result = _block.getHandle()->call(name, args.data(), args.size());
        return env->convertProxyToObject(result);
    }

    Pothos::Proxy _block;
};

static Pothos::BlockRegistry registerJavaBlock(
    "/blocks/java_block", &JavaBlock::make);
