#include <Rinternals.h>
#include <sodium.h>
#include <string.h>

SEXP R_sodium_bin2hex(SEXP bin){
  size_t bin_len = LENGTH(bin);
  size_t hex_len = bin_len * 2 + 1;
  char hex[hex_len];
  if(NULL == sodium_bin2hex(hex, hex_len, RAW(bin), bin_len))
    Rf_error("Overflow error, failed to convert to hex");
  SEXP res = PROTECT(allocVector(STRSXP, 1));
  SET_STRING_ELT(res, 0, mkChar(hex));
  UNPROTECT(1);
  return res;
}

SEXP R_sodium_hex2bin(SEXP hex, SEXP ignore){
  int hex_len = LENGTH(STRING_ELT(hex, 0));
  int max_len = hex_len / 2;
  unsigned char bin[max_len];
  size_t bin_len;
  const char * hex_end;
  if(sodium_hex2bin(bin, max_len, CHAR(STRING_ELT(hex, 0)), hex_len, CHAR(STRING_ELT(ignore, 0)), &bin_len, &hex_end))
    Rf_error("Overflow error, failed to parse hex.");
  SEXP res = allocVector(RAWSXP, bin_len);
  memcpy(RAW(res), bin, bin_len);
  return res;
}

SEXP R_randombytes_buf(SEXP length){
  size_t size = asInteger(length);
  SEXP res = allocVector(RAWSXP, size);
  randombytes_buf(RAW(res), size);
  return res;
}

SEXP R_sodium_memcmp(SEXP buf1, SEXP buf2) {
  if(LENGTH(buf1) != LENGTH(buf2))
    Rf_error("buf1 and buf2 have different lengths");
  return ScalarLogical(
    !sodium_memcmp((char*) RAW(buf1), (char*) RAW(buf2), LENGTH(buf1))
  );
}
