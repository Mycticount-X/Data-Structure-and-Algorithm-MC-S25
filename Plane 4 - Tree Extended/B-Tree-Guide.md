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

> This is AI Generated

---

📘 Apa itu B-Tree? (Ringkasan Cepat)

B-Tree adalah pohon pencarian seimbang (balanced search tree) untuk disk-based storage seperti database atau sistem file.

Setiap node punya banyak anak (tidak seperti BST).

Setiap node memiliki kunci terurut dan bisa memiliki beberapa kunci.

B-Tree didefinisikan oleh orde t (biasanya t ≥ 2), yang menentukan:

Minimal anak: t

Maksimal anak: 2t

Minimal kunci: t - 1

Maksimal kunci: 2t - 1




---

🌱 INSERT dalam B-Tree (Step-by-Step)

🔁 Langkah Umum:

1. Cari leaf node tempat key akan disisipkan.


2. Jika leaf tidak penuh, langsung sisipkan dan urutkan.


3. Jika penuh (2t−1 kunci):

Split node jadi dua

Naikkan kunci tengah ke atas (parent)

Jika parent juga penuh → split ke atas (rekursif)





---

🧪 Contoh Insert (orde t = 2)

Kondisi awal:

(empty)

1. Insert 10:

[10]

2. Insert 20:

[10 20]

3. Insert 5:

[5 10 20]  ← penuh (3 = 2t-1), harus di-split

4. Split:

Tengah = 10, naik ke atas

Bawah pecah jadi:


[10]
     /    \
 [5]     [20]

5. Insert 6:

Masuk ke kiri ([5]), jadi [5 6]


6. Insert 12:

Masuk ke kanan ([20]), jadi [12 20]



---

🧹 DELETE dalam B-Tree (Step-by-Step)

🔁 Langkah Umum:

1. Jika key ada di leaf, hapus langsung.


2. Jika key ada di internal node:

Gantikan dengan predesesor atau suksesor, lalu hapus di subtree.



3. Jika leaf kekurangan kunci (< t - 1) setelah hapus:

Lakukan merge, borrow dari sibling, atau rotate untuk menjaga minimal t-1 kunci.





---

🧪 Contoh Delete (t = 2)

[10]
     /    \
 [5 6]   [12 20]

1. Delete 6:

6 ada di leaf [5 6], langsung hapus:


[10]
     /    \
 [5]     [12 20]

2. Delete 10:

10 ada di internal node → cari suksesor = 12

Ganti 10 ← 12

Hapus 12 dari [12 20]:


[12]
     /    \
 [5]     [20]


---

🎯 Tips Pemahaman:

B-Tree menjaga keseimbangan secara otomatis.

Insert → Split ke atas bila penuh

Delete → Merge ke bawah / borrow dari sibling bila kurang

Operasi logaritmik karena tinggi pohon tetap rendah



---

Jika kamu mau, saya bisa bantu gambarkan visual insert/delete di B-Tree dalam bentuk diagram atau simulasi. Mau saya bantu visualisasikan contoh insert atau delete tertentu?

