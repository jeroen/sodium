#include <Rinternals.h>
#include <sodium.h>

/* SHA256 */

SEXP R_sha256(SEXP buf){
  SEXP res = allocVector(RAWSXP, crypto_hash_sha256_BYTES);
  if(crypto_hash_sha256(RAW(res), RAW(buf), LENGTH(buf)))
    Rf_error("Failed to hash");
  return res;
}

SEXP R_auth_sha256(SEXP buf, SEXP key){
  if(LENGTH(key) != crypto_auth_hmacsha256_BYTES)
    Rf_error("Invalid key, must be exactly %d bytes", crypto_auth_hmacsha256_BYTES);
  SEXP res = allocVector(RAWSXP, crypto_hash_sha256_BYTES);
  if(crypto_auth_hmacsha256(RAW(res), RAW(buf), LENGTH(buf), RAW(key)))
    Rf_error("Failed to hash");
  return res;
}

/* SHA512 */

SEXP R_sha512(SEXP buf){
  SEXP res = allocVector(RAWSXP, crypto_hash_sha512_BYTES);
  if(crypto_hash_sha512(RAW(res), RAW(buf), LENGTH(buf)))
    Rf_error("Failed to hash");
  return res;
}

SEXP R_auth_sha512(SEXP buf, SEXP key){
  if(LENGTH(key) != crypto_auth_hmacsha512_BYTES)
    Rf_error("Invalid key, must be exactly %d bytes", crypto_auth_hmacsha512_BYTES);
  SEXP res = allocVector(RAWSXP, crypto_hash_sha512_BYTES);
  if(crypto_auth_hmacsha512(RAW(res), RAW(buf), LENGTH(buf), RAW(key)))
    Rf_error("Failed to hash");
  return res;
}

/* BLAKE2b */

SEXP R_crypto_generichash(SEXP buf, SEXP size, SEXP key){
  int outlen = asInteger(size);
  if(outlen < crypto_generichash_BYTES_MIN || outlen > crypto_generichash_BYTES_MAX)
    Rf_error("Invalid output length, must be in between %d and %d", crypto_generichash_BYTES_MIN, crypto_generichash_BYTES_MAX);

  unsigned char *keyval = NULL;
  int keysize = 0;
  if(key != R_NilValue){
    keysize = LENGTH(key);
    keyval = RAW(key);
    if(keysize < crypto_generichash_KEYBYTES_MIN || keysize > crypto_generichash_KEYBYTES_MAX)
      Rf_error("Invalid key size, must be between %d and %d bytes", crypto_generichash_KEYBYTES_MIN, crypto_generichash_KEYBYTES_MAX);
  }

  SEXP res = allocVector(RAWSXP, outlen);
  if(crypto_generichash(RAW(res), outlen, RAW(buf), LENGTH(buf), keyval, keysize))
    Rf_error("Failed to hash");
  return res;
}

/* Shorthash */

SEXP R_crypto_shorthash(SEXP buf, SEXP key){
  if(LENGTH(key) != crypto_shorthash_KEYBYTES)
    Rf_error("Invalid key, must be exactly %d bytes", crypto_shorthash_KEYBYTES);

  SEXP res = allocVector(RAWSXP, crypto_shorthash_BYTES);
  if(crypto_shorthash(RAW(res), RAW(buf), LENGTH(buf), RAW(key)))
    Rf_error("Failed to hash");
  return res;
}
