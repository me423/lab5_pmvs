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

static ssize_t result_read(struct file *filp, char *buff, size_t len, loff_t *off)
{
	static long znak = 1;
	znak = number > 0 ? 1 : -1;
	number *= znak;

	if (number == 0) {
		result = 0;
	} else if (number == 1 || number == 2){
		result = 1;
	} else{
		long i = 0;
		long prev = 1;
		long prev2 = 1;
		for (i = 3; i <= number; i++) {
			result = prev + prev2;
			prev2 = prev;
			prev = result;
		}
	}
	result *= znak;
	return number_read(filp, buff, len, off, &result);
}


static ssize_t number_write(struct file *filp, const char *buff, size_t len, loff_t *off, long *var_pointer)
{
    if (len > BUF_SIZE) {
        return -EINVAL;
    }

    if (copy_from_user(buf, buff, len)) {
        return -EINVAL;
    }

    if (kstrtol(buf, 10, var_pointer) == -EINVAL) {
        return -EINVAL;
    }


    return len;
}

static ssize_t n_write(struct file *filp, const char *buff, size_t len, loff_t *off)
{
    return number_write(filp, buff, len, off, &number);
}

static ssize_t n_read(struct file *filp, char *buff, size_t length, loff_t * offset)
{
    return number_read(filp, buff, length, offset, &number);
}


static const struct file_operations number_fops = {
	.owner = THIS_MODULE,
	.write = n_write,
	.read = n_read,
};


static const struct file_operations result_fops = {
	.owner = THIS_MODULE,
	.read = result_read,
};

static int __init calc_init(void) {
	major_number = register_chrdev(0, NUMBER_NAME, &number_fops ); 
	if (major_number < 0) {
        	calc_exit();
        	return major_number;
    	}
	major_result = register_chrdev(0, RESULT_NAME, &result_fops );
	if (major_result < 0){
		calc_exit();
		return major_result;
	} 
	return 0;
}

static void __exit calc_exit(void) {
	if (major_number > 0){
		unregister_chrdev(major_number, NUMBER_NAME);
	}

	if (major_result > 0){
		unregister_chrdev(major_result, RESULT_NAME);
	}
}

 
 MODULE_LICENSE("GPL");
 MODULE_AUTHOR("Sultonov Abduhamid");
 module_init (calc_init);
 module_exit (calc_exit);
