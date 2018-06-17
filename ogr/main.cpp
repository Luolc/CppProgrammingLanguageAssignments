#include <iostream>
#include <string>

using namespace std;

#include "OGRPoint.h"
#include "OGRLineString.h"
#include "OGRLinearRing.h"
#include "OGRGeometryCollection.h"
#include "OGRMultiPoint.h"
#include "OGRMultiLineString.h"
#include "OGRPolygon.h"
#include "OGRMultiPolygon.h"

namespace testing {
enum OGRName {
  OGRPoint = 0,
  OGRPolygon = 1,
  OGRMultiPoint = 2,
  OGRMultiPolygon = 3
};
}

class TestGeometry {
 private:
  string OGRName2String(testing::OGRName ogrName) {
    string s = "";
    switch (testing::OGRName(ogrName)) {
      case testing::OGRPoint:s = "OGRPoint";
        break;
      case testing::OGRPolygon:s = "OGRPolygon";
        break;
      case testing::OGRMultiPoint:s = "OGRMultiPoint";
        break;
      case testing::OGRMultiPolygon:s = "OGRMultiPolygon";
        break;
      default:break;
    }
    return s;
  }

 public:
  void Test_Geometry_ImportFromWkt(string path, OGRGeometry *geometry) {
    if (path.empty() || !geometry)
      return;

    try {
      geometry->ImportFromWkt(path);
    }
    catch (exception &e) {
      cout << "Exception: " << e.what() << endl;
    }
  }

  void Test_Geometry_ExportToWkt(string path, OGRGeometry *geometry) {

    if (path.empty() || !geometry)
      return;

    try {
      geometry->ExportToWkt(path);
    }
    catch (exception &e) {
      cout << "Exception: " << e.what() << endl;
    }

  }

  void Test_Geometry(string file_path,
                     string filename_import_template,
                     string filename_export_template) {
    OGRGeometry *geometry = nullptr;
    for (int i = 0; i < 4; i++) {
      switch (testing::OGRName(i)) {
        case testing::OGRPoint:geometry = new OGRPoint();
          break;
        case testing::OGRPolygon:geometry = new OGRPolygon();
          break;
        case testing::OGRMultiPoint:geometry = new OGRMultiPoint();
          break;
        case testing::OGRMultiPolygon:geometry = new OGRMultiPolygon();
          break;
        default:break;
      }

      Test_Geometry_ImportFromWkt(
          file_path + OGRName2String(testing::OGRName(i)) + filename_import_template,
          geometry);
      Test_Geometry_ExportToWkt(
          file_path + OGRName2String(testing::OGRName(i)) + filename_export_template,
          geometry);
    }
  }
};

int main() {
  // ======= official test script begin ======
  string file_path = "wkt/";

  string filename_import_template = "_import.txt";
  string filename_export_template = "_export_official.txt";

  TestGeometry *test_geometry = new TestGeometry();
  test_geometry->Test_Geometry(file_path, filename_import_template, filename_export_template);
  // ======= official test script end ======

  auto point = OGRPoint(0, 0);
  auto b = OGRPoint(2.0, -2.5);
  point.ImportFromWkt("wkt/OGRPoint_import.txt");
  point.ExportToWkt("wkt/OGRPoint_export.txt");
  cout << point.GetMBR().ToString() << endl;
  assert(b.Equals(point));
  assert(point.Equals(b));
  cout << point.GetGeometryType() << endl;
  auto c = OGRPoint(0, 0);
  c.Copy(point);
  assert(point.Equals(c));

  cout << point.GetID() << endl;
  cout << b.GetID() << endl;
  cout << c.GetID() << endl;

  auto d = OGRLineString();
  d.AddPoint(0, 0);
  d.AddPoint(0.5, 0);
  d.AddPoint(1, 0);
  d.AddPoint(1, 2);
  d.AddPoint(1, 4);
  cout << d.GetID() << " " << d.ToString() << endl;
  cout << d.GetGeometryType() << endl;
  cout << d.GetMBR().ToString() << endl;
  cout << d.GetLength() << endl;
  auto e = OGRLineString();
  e.Copy(d);
  assert(d.Equals(e));
  e.AddPoint(5, 5);
  cout << e.GetID() << " " << e.ToString() << endl;
  assert(!d.Equals(e));
  auto f = OGRLineString();
  f.Copy(d);
  f.AddPoint(5, 5.001);
  cout << f.GetID() << " " << f.ToString() << endl;
  assert(!f.Equals(e));

  auto g = OGRLinearRing();
  g.AddPoint(0, 0);
  g.AddPoint(2, 0);
  g.AddPoint(2, 2);
  g.AddPoint(0, 2);
  g.CloseRings();
  g.CloseRings();
  cout << g.GetID() << " " << g.ToString() << endl;
  cout << g.GetGeometryType() << endl;
  cout << g.GetMBR().ToString() << endl;
  cout << g.GetLength() << endl;
  auto h = OGRLinearRing();
  h.Copy(g);
  assert(g.Equals(h));
  h.AddPoint(-1, 0);
  h.AddPoint(-1, -1);
  h.AddPoint(0, -1);
  h.CloseRings();
  assert(!h.Equals(g));
  cout << h.GetID() << " " << h.ToString() << endl;
  cout << h.GetLength() << endl;

  auto container = OGRGeometryCollection();
  container.AddGeometry(&b);
  container.AddGeometry(&d);
  container.AddGeometry(&g);
  cout << container.GetID() << " " << container.ToString() << endl;
  cout << container.GetGeometryType() << endl;
  cout << container.GetMBR().ToString() << endl;
  auto container2 = OGRGeometryCollection();
  container2.Copy(container);
  assert(container2.Equals(container));
  container2.RemoveGeometry(2);
  assert(!container.Equals(container2));
  assert(container.GetGeometry(0)->Equals(b));
  container2.AddGeometry(&h);
  assert(!container.Equals(container2));
  container2.UpdateGeometry(2, &g);
  assert(container.Equals(container2));
  cout << container2.GetID() << " " << container2.ToString() << endl;
  cout << container2.GetNumGeometries() << endl;

  auto multi_point = OGRMultiPoint();
  multi_point.ImportFromWkt("wkt/OGRMultiPoint_import.txt");
  multi_point.ExportToWkt("wkt/OGRMultiPoint_export.txt");
  cout << multi_point.GetID() << " " << multi_point.ToString() << endl;
  cout << multi_point.GetGeometryType() << endl;
  cout << multi_point.GetMBR().ToString() << endl;
  auto i = OGRMultiPoint();
  i.Copy(multi_point);
  assert(i.Equals(multi_point));
  i.AddGeometry(&b);
  assert(!multi_point.Equals(i));
  i.RemoveGeometry(2);
  assert(i.Equals(multi_point));
  cout << i.GetNumGeometries() << endl;

  auto multi_line_str = OGRMultiLineString();
  multi_line_str.AddGeometry(&d);
  multi_line_str.AddGeometry(&e);
  multi_line_str.AddGeometry(&f);
  cout << multi_line_str.GetID() << " " << multi_line_str.ToString() << endl;
  cout << multi_line_str.GetGeometryType() << endl;
  cout << multi_line_str.GetMBR().ToString() << endl;
  cout << multi_line_str.GetLength() << endl;
  auto j = OGRMultiLineString();
  j.Copy(multi_line_str);
  assert(j.Equals(multi_line_str));
  j.AddGeometry(&f);
  assert(!multi_line_str.Equals(j));
  j.RemoveGeometry(3);
  assert(multi_line_str.Equals(j));
  j.UpdateGeometry(2, &e);
  assert(!j.Equals(multi_line_str));
  assert(j.GetGeometry(2)->Equals(e));
  cout << j.GetID() << " " << j.ToString() << endl;
  cout << j.GetLength() << endl;

  auto polygon = OGRPolygon();
  polygon.ImportFromWkt("wkt/OGRPolygon_import.txt");
  polygon.ExportToWkt("wkt/OGRPolygon_export.txt");
  cout << polygon.GetID() << " " << polygon.ToString() << endl;
  cout << polygon.GetGeometryType() << endl;
  cout << polygon.GetMBR().ToString() << endl;
  cout << polygon.GetPerimeter() << endl;
  cout << polygon.GetArea() << endl;
  cout << polygon.Contains(new OGRPoint(0, 0)) << endl;
  cout << polygon.Contains(new OGRPoint(3, 3)) << endl;
  cout << polygon.Contains(new OGRPoint(5, 5)) << endl;
  auto test_line = OGRLineString();
  test_line.AddPoint(3, -3);
  test_line.AddPoint(3, 3);
  cout << polygon.Contains(&test_line) << endl;
  test_line.AddPoint(1, 1);
  cout << polygon.Contains(&test_line) << endl;
  auto test_polygon = OGRPolygon();
  test_polygon.ImportFromWktText(
      "Polygon ((-5 -5, 5 -5, 5 5, -5 5, -5 -5), (-1 -1, 1 -1, 1 1, -1 1, -1 -1))");
  cout << test_polygon.Contains(&polygon) << endl;
  auto k = OGRPolygon();
  k.Copy(polygon);
  assert(k.Equals(polygon));

  auto multi_polygon = OGRMultiPolygon();
  multi_polygon.ImportFromWkt("wkt/OGRMultiPolygon_import.txt");
  multi_polygon.ExportToWkt("wkt/OGRMultiPolygon_export.txt");
  cout << multi_polygon.GetID() << " " << multi_polygon.ToString() << endl;
  cout << multi_polygon.GetGeometryType() << endl;
  cout << multi_polygon.GetMBR().ToString() << endl;
  cout << multi_polygon.GetPerimeter() << endl;
  cout << multi_polygon.GetArea() << endl;
  cout << multi_polygon.Contains(new OGRPoint(0, 0)) << endl;
  return 0;
}