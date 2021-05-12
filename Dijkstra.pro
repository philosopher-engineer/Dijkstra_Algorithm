TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += graphs.h
HEADERS += graph_file_creator.h
HEADERS += dijkstra.h
HEADERS += dijkstra_calculator.h

SOURCES += graphs.c
SOURCES += graph_file_creator.c
SOURCES += dijkstra.c
SOURCES += dijkstra_calculator.c
SOURCES += main.c

include(deployment.pri)
qtcAddDeployment()

