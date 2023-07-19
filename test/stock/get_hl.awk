BEGIN {
  FS = "\",\""
}
{
  if(NF >= 5 && /[0-9\.]/) {
    # print($6, $5)
    printf("%d %d\n", $6 + 0.5, $5 + 0.5)
  }
}