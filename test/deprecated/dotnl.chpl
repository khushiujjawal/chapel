use Regexp;
var re1 = Regexp.compile("a.b", dotnl=true);
writeln(re1.match("a\nb").matched);
var re2 = Regexp.compile("a.b", dotAll=true);
writeln(re2.match("a\nb").matched);
