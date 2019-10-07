context("utilities")

test_that("memcmp works as expected", {
  expect_false(memcmp(charToRaw("a"), charToRaw("b")))
  expect_true(memcmp(charToRaw("a"), charToRaw("a")))
})

test_that("memcmp throws an error if length are not equal", {
  expect_error(memcmp(charToRaw("a"), charToRaw("basd")),
               "buf1 and buf2 have different lengths")
})
