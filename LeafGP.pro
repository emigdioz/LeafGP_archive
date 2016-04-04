TEMPLATE = app
CONFIG += qt warn_on thread exceptions
QT += core gui opengl concurrent
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

unix:!macx { LIBS += -L../../lib -lGLU -lopenblas -lpthread}

macx: LIBS += -L../../lib -framework OpenGL

linux-g++:QMAKE_CXXFLAGS += -fexceptions

QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3
QMAKE_LFLAGS_RELEASE -= -O1

INCLUDEPATH += ./source \
               ./source/widgets \
               ./source/widgets/jkqtmathtext \
               ./source/levmar \
               ./source/widgets/qwtplot3d \
               ./source/widgets/qwtplot3d/include \
               /home/emigdio/git_repositories/openblas/include/

SOURCES += \
    source/widgets/qwtplot3d/qwt3d_appearance.cpp \
    source/widgets/qwtplot3d/qwt3d_autoscaler.cpp \
    source/widgets/qwtplot3d/qwt3d_axis.cpp \
    source/widgets/qwtplot3d/qwt3d_color_std.cpp \
    source/widgets/qwtplot3d/qwt3d_colorlegend.cpp \
    source/widgets/qwtplot3d/qwt3d_coordsys.cpp \
    source/widgets/qwtplot3d/qwt3d_data.cpp \
    source/widgets/qwtplot3d/qwt3d_drawable.cpp \
    source/widgets/qwtplot3d/qwt3d_enrichment_std.cpp \
    source/widgets/qwtplot3d/qwt3d_extglwidget.cpp \
    source/widgets/qwtplot3d/qwt3d_function.cpp \
    source/widgets/qwtplot3d/qwt3d_graphplot.cpp \
    source/widgets/qwtplot3d/qwt3d_gridmapping.cpp \
    source/widgets/qwtplot3d/qwt3d_gridplot.cpp \
    source/widgets/qwtplot3d/qwt3d_io.cpp \
    source/widgets/qwtplot3d/qwt3d_io_reader.cpp \
    source/widgets/qwtplot3d/qwt3d_label.cpp \
    source/widgets/qwtplot3d/qwt3d_lighting.cpp \
    source/widgets/qwtplot3d/qwt3d_meshplot.cpp \
    source/widgets/qwtplot3d/qwt3d_parametricsurface.cpp \
    source/widgets/qwtplot3d/qwt3d_plot3d.cpp \
    source/widgets/qwtplot3d/qwt3d_scale.cpp \
    source/widgets/qwtplot3d/qwt3d_surfaceplot.cpp \
    source/widgets/qwtplot3d/qwt3d_types.cpp \
    source/widgets/qwtplot3d/qwt3d_volumeplot.cpp \
    source/widgets/graphwidget.cpp \
    source/widgets/qcustomplot.cpp \
    source/aboutwindow.cpp \
    source/benchmark.cpp \
    source/edge.cpp \
    source/main.cpp \
    source/mainwindow.cpp \
    source/node.cpp \
    source/worker.cpp \
    source/levmar/Axb.c \
    source/levmar/Axb_core.c \
    source/levmar/lm.c \
    source/levmar/lm_core.c \
    source/levmar/lmbc.c \
    source/levmar/lmbc_core.c \
    source/levmar/lmblec.c \
    source/levmar/lmblec_core.c \
    source/levmar/lmbleic.c \
    source/levmar/lmbleic_core.c \
    source/levmar/lmlec.c \
    source/levmar/lmlec_core.c \
    source/levmar/misc.c \
    source/levmar/misc_core.c \
    source/puppy_tree.cpp \
    source/puppy_main.cpp \
    source/puppy_primitive.cpp \
    source/mainGP.cpp \
    source/puppy_regprimitives.cpp \
    source/widgets/jkqtmathtext/jkqtmathtext.cpp \
    source/widgets/jkqtmathtext/jkqtptools.cpp

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    source/levmar/compiler.h \
    source/levmar/levmar.h \
    source/levmar/lm.h \
    source/levmar/misc.h \
    source/widgets/qwtplot3d/include/qwt3d_appearance.h \
    source/widgets/qwtplot3d/include/qwt3d_autoscaler.h \
    source/widgets/qwtplot3d/include/qwt3d_axis.h \
    source/widgets/qwtplot3d/include/qwt3d_color.h \
    source/widgets/qwtplot3d/include/qwt3d_color_std.h \
    source/widgets/qwtplot3d/include/qwt3d_colorlegend.h \
    source/widgets/qwtplot3d/include/qwt3d_coordsys.h \
    source/widgets/qwtplot3d/include/qwt3d_data.h \
    source/widgets/qwtplot3d/include/qwt3d_drawable.h \
    source/widgets/qwtplot3d/include/qwt3d_enrichment.h \
    source/widgets/qwtplot3d/include/qwt3d_enrichment_std.h \
    source/widgets/qwtplot3d/include/qwt3d_extglwidget.h \
    source/widgets/qwtplot3d/include/qwt3d_function.h \
    source/widgets/qwtplot3d/include/qwt3d_global.h \
    source/widgets/qwtplot3d/include/qwt3d_graphplot.h \
    source/widgets/qwtplot3d/include/qwt3d_gridmapping.h \
    source/widgets/qwtplot3d/include/qwt3d_gridplot.h \
    source/widgets/qwtplot3d/include/qwt3d_helper.h \
    source/widgets/qwtplot3d/include/qwt3d_io.h \
    source/widgets/qwtplot3d/include/qwt3d_io_reader.h \
    source/widgets/qwtplot3d/include/qwt3d_label.h \
    source/widgets/qwtplot3d/include/qwt3d_mapping.h \
    source/widgets/qwtplot3d/include/qwt3d_meshplot.h \
    source/widgets/qwtplot3d/include/qwt3d_openglhelper.h \
    source/widgets/qwtplot3d/include/qwt3d_parametricsurface.h \
    source/widgets/qwtplot3d/include/qwt3d_plot3d.h \
    source/widgets/qwtplot3d/include/qwt3d_portability.h \
    source/widgets/qwtplot3d/include/qwt3d_scale.h \
    source/widgets/qwtplot3d/include/qwt3d_surfaceplot.h \
    source/widgets/qwtplot3d/include/qwt3d_types.h \
    source/widgets/qwtplot3d/include/qwt3d_valueptr.h \
    source/widgets/qwtplot3d/include/qwt3d_volumeplot.h \
    source/widgets/graphwidget.h \
    source/widgets/qcustomplot.h \
    source/aboutwindow.h \
    source/edge.h \
    source/mainwindow.h \
    source/matrix.h \
    source/node.h \
    source/worker.h \
    source/puppy_regprimitives.hpp \
    source/puppy_tokenT.hpp \
    source/puppy_randomizer.hpp \
    source/puppy_tree.hpp \
    source/puppy_main.hpp \
    source/puppy_primitiveinline.hpp \
    source/puppy_primitivehandle.hpp \
    source/puppy_primitive.hpp \
    source/puppy_context.hpp \
    source/widgets/jkqtmathtext/jkqtmathtext.h \
    source/widgets/jkqtmathtext/jkqtp_imexport.h \
    source/widgets/jkqtmathtext/jkqtptools.h

FORMS += \
    source/mainwindow.ui \
    source/aboutwindow.ui

RESOURCES += \
    images.qrc
