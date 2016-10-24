#include <linux/kernel.h>
 #include <linux/module.h>
 #include <linux/device.h>
 #include <linux/string.h>
 #include <linux/fs.h>
 #include <asm/uaccess.h>
 
 
 #define NUMBER_NAME "calc_number"
 #define RESULT_NAME "calc_result"
 #define BUF_SIZE 128
 
 static int major_number = -1;
 static int major_result = -1;
 static long number = 0;
 static long result = 0;
 
 
 static int calc_init(void);
 static void calc_exit(void);
 static ssize_t n_read(struct file *, char *, size_t, loff_t *);
 static ssize_t n_write(struct file *, const char *, size_t, loff_t *);
 static ssize_t number_read(struct file *, char *, size_t, loff_t *, long *);
 static ssize_t result_read(struct file *, char *, size_t, loff_t *);
 static ssize_t number_write(struct file *, const char *, size_t, loff_t *, long *);
 
 static char buf[BUF_SIZE] = { 0 };
 
 static ssize_t number_read(struct file *filp, char *buff, size_t len, loff_t *off, long *var_pointer)
 {
     ssize_t size;
 
     if (*off != 0) {
         return 0;
     }
 
     snprintf(buf, BUF_SIZE, "%ld", *var_pointer);
 
     size = strlen(buf);
 
     if (size >= len) {
         return -EINVAL;
     }
 
     if (copy_to_user(buff, buf, size)) {
         return -EINVAL;
     }
 
     *off = size;
     return size;
 }
 
 
 
 MODULE_LICENSE("GPL");
 MODULE_AUTHOR("Sultonov Abduhamid");
 module_init (calc_init);
 module_exit (calc_exit);
