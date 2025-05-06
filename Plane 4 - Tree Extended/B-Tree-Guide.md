## 🌳 **Langkah-Langkah Insert pada B-Tree**

1. **Mulai dari root.**
2. Jika root penuh (memiliki `2t - 1` kunci):

   * Buat node baru sebagai root.
   * Pecah root lama menjadi dua dan promosikan median ke root baru.
3. **Temukan posisi yang sesuai untuk penyisipan**:

   * Turun ke anak yang sesuai, pecah anak tersebut jika penuh **sebelum turun lebih jauh**.
4. Ulangi langkah 3 hingga mencapai node yang **tidak penuh**.
5. **Sisipkan kunci** ke posisi yang sesuai dalam node tersebut (secara terurut).
6. Selesai.

---

## 🔥 **Langkah-Langkah Delete pada B-Tree**

Misal kita ingin menghapus kunci `K` dari B-Tree:

1. **Temukan posisi `K`.**
2. Jika `K` ada di **node daun**, langsung hapus dari node tersebut.
3. Jika `K` ada di **node internal**:

   * Cari **predecessor** atau **successor** dari `K`:

     * Gantikan `K` dengan salah satu dari mereka.
     * Hapus predecessor/successor dari subtree yang sesuai.
4. Jika `K` tidak ada di node saat ini:

   * **Turun ke anak yang sesuai** untuk mencari `K`.
   * Sebelum turun:

     * Jika anak tujuan memiliki **kurang dari `t` kunci**, lakukan salah satu:

       * **Pinjam** kunci dari saudara sebelah jika memungkinkan.
       * **Gabungkan** dengan saudara jika keduanya memiliki `t - 1` kunci.
   * Lanjutkan proses hingga menemukan dan menghapus `K`.
5. Ulangi penyesuaian struktur hingga semua node memenuhi properti B-Tree.

---