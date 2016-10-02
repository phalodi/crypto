#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0

int is_prime(int n);
int gcd(int a, int b);
int power_mod(int b, int e, int n);
void generate_key(int p, int q, int *public_key, int *private_key,
                  int *cipher_modulus);
int encrypt_message(int flen, char *from, int *to, int e, int n);
int decrypt_message(int flen, int *from, char *to, int d, int n);


int main(int argc, char *argv[]) {

  // Message buffers
  char *input_message = "hello, world !";
  int  *encrypted_message;
  char *decrypted_message;

  // RSA Key components
  int private_key;
  int public_key;
  int cipher_modulus;

  // Choose two disctinc, prime numbers p and q to grenerate the key pairs
  generate_key(61, 53, &private_key, &public_key, &cipher_modulus);

  // output generated keys
  printf("Generated public key: %d\n", public_key);
  printf("Generated private key: %d\n", private_key);
  printf("Cipher modulus: %d\n", cipher_modulus);

  printf("input message: %s\n", input_message);

  // Allocate message buffers
  int message_len = strlen(input_message);
  encrypted_message = (int *) malloc(message_len * sizeof(int));
  decrypted_message = (char *) malloc(message_len * sizeof(char));

  // Encrypt input_message to encrypted_message using public_key.
  // Each characters is encrypted using it's ASCII value,
  // the encrypted_message cannot be read in ASCII.
  encrypt_message(message_len, input_message, encrypted_message,
                  private_key, cipher_modulus);

  // Decrypt encrypted_message using private_key.
  // The decrypted_message can be read back in ASCII.
  decrypt_message(message_len, encrypted_message, decrypted_message,
                  public_key, cipher_modulus);

  printf("decrypted message: %s\n", decrypted_message);

  return 0;

}

/**
 * Check if n is a prime number
 *
 * @param n number to check
 * @return true(1) or false(0)
 */
int is_prime(int n) {
  if (n <= 1) {
    return false;
  } else if (n <= 3) {
    return true;
  } else if (n % 2 == 0 || n % 3 == 0) {
    return false;
  }
  int i = 5;
  while (i * i <= n) {
    if (n % i == 0 || n % (i + 1) == 0) {
      return false;
    }
    i = i + 6;
  }
  return true;
}

/**
 * Greatest Common divisor
 *
 * @param a
 * @param b
 */
int gcd(int a, int b) {
  int c;
  while (a != 0) {
    c = a;
    a = b % a;
    b = c;
  }
  return b;
}

/**
 * Modular exponentiation
 * i.e. pow(a,b) % n for big numbers
 * Right-to-left binary method
 * Big-O(log e)
 *
 * @param b the base
 * @param e the exponent
 * @param n the modulus
 */
int power_mod(int b, int e, int n) {
  long long result = 1;
  long long  base = b;
  while (e > 0) {
    if (e % 2 == 1) {
      // exponent is odd
      result = (result * base) % n;
    }
    base = (base * base) % n;
    e = e / 2;
  }
  return result % n;
}

/**
 * Generate RSA private and public key using two distinc prime numbers
 * the keys are written to the private_key, public_key and cipher_modulus
 * pointers.
 * The first possible set of keys is used.
 *
 * @param p              prime number p
 * @param q              prime number q
 * @param public_key     public key destination
 * @param private_key    private key destination
 * @param cipher_modulus cipher modulus destination
 */
void generate_key(int p, int q, int *public_key, int *private_key,
                  int *cipher_modulus) {
  assert(p != q);
  assert(is_prime(p));
  assert(is_prime(q));

  // 1.
  // n: cipher modulus for both the private and public keys
  // its length usually expressed in bits, is the key length
  int n = p * q;
  *cipher_modulus = n;
  printf("n = %d\n", n);

  // 2.
  // phi: Euler's  totient function
  // this value is kept private
  int phi =  (p - 1) * (q - 1);
  printf("phi = %d\n", phi);

  // 3. Public key:e generation
  // Choose an integer e such that 1 < e < phi and gcd(e, phi) = 1
  // i.e. e and phi are coprime
  int e;
  for (int i = phi; i > 1; i--) {
    if (gcd(i, phi) == 1) {
      e = i;
    }
  }
  *public_key = e;
  printf("e = %d\n", e);

  // 4. Private key: d generation
  // Determine d as d = e^-1 (mod phi)
  // i.e solve for d given d * e = 1 % phi
  int d;
  int i = 0;
  while ((i * e) % phi != 1) {
    i++;
  }
  d = i;
  *private_key = d;
  printf("d = %d\n", d);
}

/**
 * Encrypt each character using it's ASCII value
 * Note: no padding scheme is implemented here
 *
 * @param flen  clear text message length
 * @param from  clear text message
 * @param to    ciphered text destination
 * @param e     public key
 * @param n     cipher modulus
 * @return flen
 */
int encrypt_message(int flen, char *from, int *to, int e, int n) {
  for (int i = 0; i < flen; i++) {
    assert(from[i] < n);
    to[i] = power_mod(from[i], e, n); // c = m^e % n
  }
  return flen;
}

/**
 * Decrypt each ciphered number into a character
 *
 * @param flen  ciphered text message length
 * @param from  ciphered message
 * @param to    decrypted message destination
 * @param d     private key
 * @param n     cipher modulus
 * @return flen
 */
int decrypt_message(int flen, int *from, char *to, int d, int n) {
  for (int i = 0; i < flen; i++) {
    to[i] = power_mod(from[i], d, n); // m = c^d % n
  }
  return flen;
}
