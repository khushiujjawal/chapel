use UnitTest;
var sep = "=="*40;
var x1 = 1..5;
var y1 = 1..6;
try {
  UnitTest.assertGreaterThan(x1,y1);
}
catch e {
  writeln(e);
  writeln(sep);
}
try {
  UnitTest.assertGreaterThan(y1,y1);
}
catch e {
  writeln(e);
  writeln(sep);
}
