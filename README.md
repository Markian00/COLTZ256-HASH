# COLTZ256-HASH
This work is an original product of mine, however, I drew inspiration from independent researcher Fabian Bocart after reading his paper on "Inflation Propensity of Collatz Orbits" in the Journal of Risk and Financial Management.

Here I have created a cryptographic hash function with a 256-bit output leveraging the properties of the unsolved Collatz Conjecture. SHA-256 is perhaps the best-known hashing algorithm today. In 2017 a technical flaw in SHA-256 was documented that allowed for optimizations (for example "ASIC-BOOST") which put certain individuals ahead of the curve in cryptocurrency mining (Risking a 50% attack on the blockchain). By exploiting collisions of similar headers in the blockchain when hashing they could mine several times faster than competing "miners". SHA-256's flaws make it exploitable, meaning it may not be a reliable algorithm for cryptographic hashing. Our over-reliance on SHA-256 is clear to SWE around the globe, so we need alternatives (and replacements) to ensure communal welfare if the worst were to happen.

Hash Collision Analysis:

Proof of Non-Invertibility:

Utility in WEB3 development and Cryptography:

