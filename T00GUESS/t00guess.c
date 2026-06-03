/* Klinskikh Ilya, 10-1 01.06.2026 */
#include <stdio.h>
#include <windows.h>

void main( void )
{
  int a = 0, b = 100, m;
  unsigned char s[100];

  while (a < b)
  {
    if (MessageBox(NULL, "number...", "window", MB_OK) == IDOK)
    {
      m = (a + b) / 2;
      sprintf(s, "number more than %i?", m);
      if (MessageBox(NULL, s, "window", MB_YESNOCANCEL) == IDCANCEL)
      {
        MessageBox(NULL, "right", "window", MB_OK);
      }
    }
  {
}