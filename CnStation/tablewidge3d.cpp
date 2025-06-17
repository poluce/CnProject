#include "tablewidge3d.h"


#include <QHeaderView>
#include <QItemModelBarDataProxy>
#include <QMessageBox>
#include <QScreen>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QCategory3DAxis>
#include <QTimer>

TableWidge3D::TableWidge3D(QWidget *parent) : QWidget(parent)
{
    m_graph = new Q3DBars();
    QWidget *container = QWidget::createWindowContainer(m_graph);

    if (!m_graph->hasContext()) {
        QMessageBox::warning(this,"openGL窗口初始化失败","Couldn't initialize the OpenGL context");
    }

    QSize screenSize = m_graph->screen()->size();
//    container->setMinimumSize(QSize(screenSize.width() / 2, screenSize.height() / 2));
    container->setMaximumSize(screenSize);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container->setFocusPolicy(Qt::StrongFocus);

    m_graph->setSelectionMode(QAbstract3DGraph::SelectionItemAndRow);

    QVBoxLayout *layout = new QVBoxLayout(this);
    m_tableWidget = new QTableWidget;
    layout->addWidget(container, 1);
    layout->setMargin(0);
    layout->setSpacing(0);

    setupModel();

    m_tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_tableWidget->setAlternatingRowColors(true);
    this->setWindowTitle(QStringLiteral("Hours spent on the Internet"));

    QItemModelBarDataProxy *proxy = new QItemModelBarDataProxy(m_tableWidget->model());
    proxy->setUseModelCategories(true);
    QBar3DSeries *series = new QBar3DSeries(proxy);

    QLinearGradient gradient;
    gradient.setColorAt(0.0, "#dcbd63");
    gradient.setColorAt(1.0, Qt::yellow);
    series->setBaseGradient(gradient);
    series->setColorStyle(Q3DTheme::ColorStyleRangeGradient);

    //设置基本色调
//    series->setBaseColor(QColor("#dcbd63"));
    series->setMesh(QAbstract3DSeries::MeshBar);

    m_graph->addSeries(series);
//    m_graph->addSeries(series2);
    setupCleanView();
}

void TableWidge3D::setupModel()
{
    float hours[10][10] = {{2.0f,2.0f, 2.0f, 2.0f, 0, 0, 2.0f, 2.0f, 2.0f, 2.0f},
                         {2.0f,2.0f, 2.0f, 2.0f, 0, 0, 2.0f, 2.0f, 2.0f, 2.0f},
                         {2.0f,2.0f, 2.0f, 2.0f, 0, 0, 2.0f, 2.0f, 2.0f, 2.0f},
                         {2.0f,2.0f, 2.0f, 2.0f, 0, 0, 2.0f, 2.0f, 2.0f, 2.0f},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {2.0f,2.0f, 2.0f, 2.0f, 0, 0, 2.0f, 2.0f, 2.0f, 2.0f},
                         {2.0f,2.0f, 2.0f, 2.0f, 0, 0, 2.0f, 2.0f, 2.0f, 2.0f},
                         {2.0f,2.0f, 2.0f, 2.0f, 0, 0, 2.0f, 2.0f, 2.0f, 2.0f},
                         {2.0f,2.0f, 2.0f, 2.0f, 0, 0, 2.0f, 2.0f, 2.0f, 2.0f},
                         };

    m_tableWidget->setRowCount(10);
    m_tableWidget->setColumnCount(10);
//    m_tableWidget->horizontalHeader()->setVisible(false);
//    m_tableWidget->verticalHeader()->setVisible(false);


    for (int i = 0; i < m_tableWidget->rowCount(); i++)
    {
        for (int j = 0; j < m_tableWidget->columnCount(); j++)
        {
            QModelIndex index = m_tableWidget->model()->index(i, j);
            m_tableWidget->model()->setData(index, hours[i][j]);
        }
    }
}

void TableWidge3D::setupCleanView()
{
    // 获取当前主题
    Q3DTheme* currentTheme = m_graph->activeTheme();

    // 禁用网格线
    currentTheme->setGridEnabled(false);

    // 禁用背景
    currentTheme->setBackgroundEnabled(false);

    // 设置背景色为透明或白色
//    currentTheme->setBackgroundColor(QColor("#3b7d89"));

     currentTheme->setWindowColor(QColor("#3b7d89"));

    // 设置空标签列表来隐藏标签
    m_graph->rowAxis()->setLabels(QStringList());
    m_graph->columnAxis()->setLabels(QStringList());
    m_graph->valueAxis()->setLabels(QStringList());

    m_graph->rowAxis()->setLabels(QStringList());   // 无内容
    //设置光照阴影
    m_graph->setShadowQuality(QAbstract3DGraph::ShadowQualitySoftHigh);

    // 隐藏所有轴标题
    m_graph->rowAxis()->setTitleVisible(false);
    m_graph->columnAxis()->setTitleVisible(false);
    m_graph->valueAxis()->setTitleVisible(false);

    // 禁用标签背景
    currentTheme->setLabelBackgroundEnabled(false);
    m_graph->valueAxis()->setLabelFormat(QString());  // 不显示任何格式

    // 设置标签字体颜色为透明，彻底让文字不可见
    Q3DTheme *theme = m_graph->activeTheme();
    theme->setLabelTextColor(Qt::transparent);

    //设置视角
    m_graph->scene()->activeCamera()->setCameraPosition(37.0f, 41.0f);
    m_graph->scene()->activeCamera()->setZoomLevel(74);

    m_graph->valueAxis()->setRange(0, 5);  // 改变 Y 轴最大值，缩短相对高度
    m_graph->setBarSpacing(QSizeF(0.5f, 0.1f));  // 横向、纵向的间隔

//    m_graph->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPresetIsometricLeftHigh);

//    QTimer *camMonitorTimer = new QTimer(this);
//    connect(camMonitorTimer, &QTimer::timeout, this, [=]() {
//        Q3DCamera *camera = m_graph->scene()->activeCamera();
//        qDebug() << "Camera Position:";
//        qDebug() << "  Horizontal Angle:" << camera->xRotation(); // 水平角度
//        qDebug() << "  Vertical Angle:" << camera->yRotation();   // 俯仰角度
//        qDebug() << "  Zoom Level:" << camera->zoomLevel();       // 缩放倍数
//    });
//    camMonitorTimer->start(100); // 每 100ms 输出一次
}

