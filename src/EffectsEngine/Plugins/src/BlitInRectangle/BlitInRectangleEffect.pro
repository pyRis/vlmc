######################################################################
# Automatically generated by qmake (2.01a) Sun Nov 29 13:42:14 2009
######################################################################


TARGET =      VLMC_BlitInRectangleEffectPlugin
TEMPLATE      = lib
CONFIG       += plugin
INCLUDEPATH  += . ../../../PluginsAPI
HEADERS      += BlitInRectangleEffectPlugin.h \
                BlitInRectangleEffectPluginCreator.h \
                ../../../PluginsAPI/IEffectNode.h \
                ../../../PluginsAPI/IEffectPlugin.h \
                ../../../PluginsAPI/IEffectPluginCreator.h \
                ../../../PluginsAPI/InSlot.hpp \
                ../../../PluginsAPI/OutSlot.hpp \
                ../../../PluginsAPI/LightVideoFrame.h
SOURCES      += BlitInRectangleEffectPlugin.cpp BlitInRectangleEffectPluginCreator.cpp ../../../PluginsAPI/LightVideoFrame.cpp
DESTDIR       = ../../bin
