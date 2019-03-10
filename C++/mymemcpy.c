//  实现一个Memcpy函数

void *mymemcpy(void *dst,void *src,size_t len)
{
    char *pdst = NULL;
    char *psrc = NULL;

    if(dst == NULL || src == NULL || len <= 0){
        return NULL;
    }

    if(src < dst && (char*)src + len > (char*)dst){
        psrc = (char *)src + len - 1;
        pdst = (char *)dst + len - 1;
        while(len){
            *pdst-- = *psrc--;
            len--;
        }
    }else{
        psrc = (char *)src;
        pdst = (char *)dst;
        while(len){
            *pdst++ = *psrc++;
             len--;
        }
    }
    return dst;
}