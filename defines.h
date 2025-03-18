#define NUM "0123456789"
#define ALPHA "abcdefghijklmnopqrustuvwxyz" \
			  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define ALNUM ALPHA NUM
#define forin(i, stop) \
        typeof(stop) stop_ = (stop); \
        for (int i = 0; i < stop_; i++)
