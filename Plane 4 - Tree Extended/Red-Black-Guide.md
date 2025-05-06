### 🔴⚫ **Langkah-langkah Insert dalam Red-Black Tree**

1. **Buat node baru `z`** dengan nilai yang ingin dimasukkan, beri warna **MERAH**.

2. **Cari posisi yang tepat untuk menyisipkan `z`** seperti pada binary search tree:

   * Mulai dari akar (`root`).
   * Bandingkan `z.key` dengan node saat ini.
   * Bergerak ke kiri jika lebih kecil, ke kanan jika lebih besar, hingga menemukan `NIL`.

3. **Sisipkan node `z`** sebagai anak kiri atau kanan dari node induk (`parent`) yang ditemukan.

4. **Setel anak kiri dan kanan `z` menjadi `NIL`, dan warnai `z` sebagai MERAH**.

5. **Lakukan perbaikan (`Insert-Fixup`)** untuk memastikan semua sifat Red-Black Tree tetap terpenuhi:

   * Selama `parent(z)` berwarna MERAH:

     * Tentukan apakah `parent(z)` adalah anak kiri atau kanan dari `grandparent(z)`.
     * Temukan `uncle(z)` (saudara dari `parent(z)`).
     * Jika `uncle(z)` berwarna MERAH:

       * Ubah warna `parent(z)` dan `uncle(z)` menjadi HITAM.
       * Ubah warna `grandparent(z)` menjadi MERAH.
       * Geser `z` ke `grandparent(z)` dan ulangi.
     * Jika `uncle(z)` berwarna HITAM:

       * Jika `z` adalah anak kanan dan `parent(z)` adalah anak kiri:

         * Lakukan rotasi kiri pada `parent(z)` → ubah `z` menjadi `parent(z)`.
       * Jika `z` adalah anak kiri dan `parent(z)` adalah anak kanan:

         * Lakukan rotasi kanan pada `parent(z)` → ubah `z` menjadi `parent(z)`.
       * Warnai `parent(z)` HITAM dan `grandparent(z)` MERAH.
       * Lakukan rotasi (kanan atau kiri) pada `grandparent(z)`.

6. **Setel akar (`root`) menjadi HITAM.**
