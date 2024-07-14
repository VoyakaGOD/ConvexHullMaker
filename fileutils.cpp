#include "fileutils.h"

bool FileUtils::createSVG(const QList<QPoint> &points, const QList<QPoint> &hull, QString savePath, const PointsAndHullStyle &style)
{
    if(points.empty() || hull.empty())
        return false;

    QFile file(savePath);
    if(!file.open(QIODevice::WriteOnly))
        return false;

    QTextStream out(&file);
    out << "<?xml version=\"1.0\"\n"
           "    encoding=\"UTF-8\"?>\n"
           "<svg version=\"1.1\"\n"
           "    baseProfile=\"full\"\n"
           "    xmlns=\"http://www.w3.org/2000/svg\"\n"
           "    xmlns:xlink=\"http://www.w3.org/1999/xlink\"\n"
           "    xmlns:ev=\"http://www.w3.org/2001/xml-events\"\n"
           "    width=\"100%\"\n"
           "    height=\"100%\">\n\n";

    out << "    <path fill=\"none\" stroke=\"" << style.hullLineColor.name() << "\" stroke-width=\"" << style.hullLineWidth << "\"\n"
           "        d=\"";

    auto it = hull.begin();
    out << "M " << (*it).x() << " " << (*it).y() << "\n";
    while((++it) < hull.end())
    {
        out << "        L " << (*it).x() << " " << (*it).y() << "\n";
    }

    out << "        Z\" />\n\n";

    out << "    <g stroke=\"" << style.pointStrokeColor.name() << "\" stroke-width=\""
        << style.pointStrokeWidth << "\" fill=\"" << style.pointColor.name() << "\">\n";

    for(auto point : points)
        out << "        <circle cx=\"" << point.x() << "\" cy=\"" << point.y() << "\" r=\"" << style.pointSize << "\" />\n";

    out << "    </g>\n\n";

    out << "</svg>";

    file.close();
    return true;
}

QString FileUtils::getVacantName(QString name)
{
    if(!QFile::exists(name))
        return name;

    QFileInfo fileInfo(name);
    QString extension = fileInfo.suffix();
    QDir directory = fileInfo.absoluteDir();

    directory.setFilter(QDir::Filter::Files);
    return name.left(name.lastIndexOf(".")) + QString::number(directory.count()) + "." + extension;
}
