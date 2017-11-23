void MakeHTML()
{
  THtml h;
  h.SetDocPath("./htmldoc");
  h.SetInputDir("$(ROOTSYS):./");
  h.MakeAll(kFALSE, "CRT*");
  h.MakeIndex("CRT*");
 // h.CreateJavascript();
 // h.CreateStylesheet();
}
