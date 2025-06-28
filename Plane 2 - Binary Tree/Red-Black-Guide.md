### 🔴⚫ **Langkah-langkah Insert dalam Red-Black Tree**

> Note: This is AI Generated Markdown

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




Tentu! Proses **deletion (penghapusan)** pada **Red-Black Tree (RBT)** lebih kompleks dibanding BST biasa karena kita harus menjaga **aturan warna** dan **keseimbangan pohon**.

Mari kita bahas **step-by-step**: mulai dari **konsep**, lalu **kasus-kasus utama**, dan terakhir **langkah penyesuaian (fix-up)**.

---

## 🧠 🔴⚫ Apa itu Red-Black Tree?

Red-Black Tree adalah pohon pencarian biner (BST) **yang seimbang** dengan aturan:

1. Setiap simpul berwarna merah atau hitam.
2. Root selalu hitam.
3. Semua daun (NIL) adalah **node hitam khusus**.
4. Jika node merah, maka anaknya **harus hitam** (tidak boleh merah-merah berturut-turut).
5. Setiap jalur dari node ke daun memiliki jumlah **hitam yang sama**.

---

## 🧹 Tujuan Deletion

Sama seperti BST biasa: menghapus node, **tetapi kita harus menjaga 5 aturan di atas tetap valid**. Deletion di RBT jauh lebih kompleks karena penghapusan node **hitam** dapat melanggar keseimbangan warna pohon.

---

## 🔧 STEP-BY-STEP DELETION

---

### 🟢 **STEP 1: Hapus seperti BST biasa**

* Jika node punya 0 atau 1 anak → hapus langsung dan ganti dengan anaknya.
* Jika punya 2 anak → cari **in-order successor**, tukar, lalu hapus successor.

Tetapi: kita harus tahu warna node **yang dihapus**, dan warna node **pengganti**.
Kalau node yang dihapus **hitam**, bisa melanggar aturan black-height → perlu fix.

---

### 🟡 **STEP 2: Tandai node pengganti sebagai "x"**

* Ini adalah node yang naik menggantikan node yang dihapus (bisa NIL)
* Simpan warnanya, jika yang dihapus adalah **hitam**, maka kita butuh **fix-up**

---

### 🔴 **STEP 3: Red-Black Fix-Up**

Jika node yang dihapus berwarna hitam → bisa menyebabkan **double black** (terlalu banyak hitam di jalur) → perlu koreksi.

---

## ⚠️ Kasus-kasus Fix-Up (pada node `x`):

Asumsikan `x` adalah node pengganti (bisa node aktual atau NIL) yang kita perbaiki, dan `w` adalah saudara dari `x`.

---

### 📘 **Case 1: Saudara `w` merah**

* Ubah warna `w` → hitam
* Ubah warna `parent(x)` → merah
* **Rotate** terhadap `parent(x)` → kita ubah struktur supaya jadi kasus 2, 3, atau 4

---

### 📘 **Case 2: Saudara `w` hitam, dan kedua anaknya hitam**

* Ubah `w` → merah
* Pindah double black ke `parent(x)` dan ulangi fix-up di atas

---

### 📘 **Case 3: Saudara `w` hitam, dan anak kiri `w` merah, anak kanan hitam**

* Rotate `w` ke kanan
* Tukar warna `w` dan anak kirinya → jadi case 4

---

### 📘 **Case 4: Saudara `w` hitam, dan anak kanan `w` merah**

* Ubah warna `w` jadi warna `parent(x)`
* Ubah `parent(x)` dan anak kanan `w` jadi hitam
* Rotate `parent(x)` ke kiri
* Fix selesai

---

## ✍️ Simulasi Ringkas

Misalnya:

```
    10B
   /   \
  5B   15B
       /
     12R
```

Hapus `12R`: tidak masalah, karena merah → langsung hapus.

Tapi kalau:

```
    10B
   /   \
  5B   15B
```

Hapus `5B`: ini hitam → menyebabkan **black imbalance** → kita aktifkan fix-up.

---

## 🔚 Ringkasan Langkah-langkah Deletion RBT

| Langkah | Deskripsi                                       |
| ------- | ----------------------------------------------- |
| 1.      | Hapus seperti BST biasa                         |
| 2.      | Tandai node pengganti sebagai `x`               |
| 3.      | Jika node yang dihapus merah → selesai          |
| 4.      | Jika hitam → lakukan fix-up mulai dari `x`      |
| 5.      | Jalankan fix-up hingga aturan RBT kembali valid |

---

## 🎓 Tips Menguasai RBT Deletion

* Fokus dulu pahami BST deletion
* Latih tracing fix-up: lakukan step-by-step untuk setiap **case 1–4**
* Gunakan warna visual saat menggambar pohon
* Lihat tutorial interaktif seperti: [https://www.cs.usfca.edu/\~galles/visualization/RedBlack.html](https://www.cs.usfca.edu/~galles/visualization/RedBlack.html)

