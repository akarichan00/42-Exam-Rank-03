#include <stdlib.h>  
#include <unistd.h> 

#define BUFFER_SIZE 5

int    ft_strlen(char *str)
{
    int    i;

    i = 0;
    while (str && str[i])
        i++;
    return (i);
}

char    *ft_strjoin(char *s1, char *s2)
{
    int        i;
    int        k;
    int        j;
    char    *ret;

    if (s1 == NULL && s2 == NULL)
        return (0);
    i = 0;
    k = 0;
    j = 0;
    ret = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    if (!ret)
        return (0);
    while (s1 && s1[k] != '\0')
        ret[i++] = s1[k++];
    while (s2 && s2[j] != '\0')
        ret[i++] = s2[j++];
    ret[i] = '\0';
    free(s1);
    return (ret);
}

char    *ft_strchr(const char *s, int c)
{
    int    i;

    i = 0;
    while (s && s[i] != '\0')
        if (s[i++] == (char)c)
            return ((char *)&s[i - 1]);
    return (0);
}

char    *bruh(char *s, int start, int end, int fr)
{
    char    *ret;
    int        i;

    i = 0;
    if (end >= start && !(end == start && s[start] == '\0'))
    {
        ret = malloc(end - start + 2);
        while (start <= end)
            ret[i++] = s[start++];
        ret[i] = '\0';
        if (fr)
            free(s);
        return (ret);
    }
    if (fr)
        free(s);
    return (0);
}

char    *get_next_line(int fd)
{
    char        *hold;
    char        buffer[BUFFER_SIZE + 1];
    static char    *left;
    int            i;
    int            len;

    len = -1;
    i = 0;
    hold = ft_strjoin(left, 0);
    while (len != 0 && !ft_strchr(hold, '\n'))
    {
        len = read(fd, buffer, BUFFER_SIZE);
        if (len < 0)
            return (0);
        buffer[len] = '\0';
        hold = ft_strjoin(hold, buffer);
    }
    while (hold && hold[i] && hold[i] != '\n')
        i++;
    left = bruh(hold, i + 1, ft_strlen(hold), 0);
    return (bruh(hold, 0, i, 1));
} 

#include <fcntl.h>
#include <stdio.h>

int main()
{
    int fd = open("test.txt", O_RDONLY);
    char *line;

    if (fd == -1)
    {
        printf("Failed to open file\n");
        return 1;
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s\n", line);
        free(line);
    }

    close(fd);
    return 0;
}
