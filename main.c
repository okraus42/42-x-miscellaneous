/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:04:32 by okraus            #+#    #+#             */
/*   Updated: 2023/02/22 18:37:31 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	*ft_print_memory(void *addr, int fd, unsigned int size);

//void	*ft_print_memory_2(void *addr, int fd, unsigned int size);

static int	ft_put_bit(const unsigned char c, int fd)
{
	if (c & 0x80)
		write(fd, "1", 1);
	else
		write(fd, "0", 1);
	return (1);
}

int	ft_put_bin(void *addr, int fd)
{
	unsigned char	c;
	int				i;
	int				r;

	i = 8;
	r = 0;
	c = *(unsigned char *) addr;
	while (i)
	{
		ft_put_bit(c, fd);
		i--;
		c <<= 1;
	}
	return (r);
}

static void	ft_put_hex(void *addr, int fd)
{
	unsigned int	i;
	unsigned char	*s;

	i = 0;
	s = (unsigned char *) addr;
	write(fd, &"0123456789abcdef"[s[i] / 16], 1);
	write(fd, &"0123456789abcdef"[s[i] % 16], 1);
}

int	main(void)
{
	unsigned char	a[17] = "0123456789abcdef";
	unsigned char	b;
	unsigned char	s[200] = "0123456789abc\200defghijkl\n\t\vafdadsfhaghag";
	unsigned int	u;
	unsigned long	l;
	unsigned int	*x;
	void			*c;
	int				fd;

	fd = 1;
	b = 'b';
	printf("a[5] = %c\n", a[5]);
	printf("*(a + 5) = %c\n", *(a + 5));
	printf("5[a] = %c\n", 5[a]);
	printf("*(5 + a) = %c\n\n", *(5 + a));
	printf("b: %c | %x\n\n", b, b);
	b = b & 'B';
	printf("b = b & 'B';\n");
	ft_put_bin((void *)&b, fd);
	write (fd, "\n", 1);
	printf("b: %c | %x\n\n", b, b);
	b = b & 0xFF;
	printf("b = b & 0xFF;\n");
	ft_put_bin((void *)&b, fd);
	write (fd, "\n", 1);
	printf("b: %c | %x\n\n", b, b);
	b = b | 0x20;
	printf("b = b | 0x20;\n");
	ft_put_bin((void *)&b, fd);
	write (fd, "\n", 1);
	printf("b: %c | %x\n\n", b, b);
	b >>= 1;
	printf("b >>= 1;\n");
	ft_put_bin((void *)&b, fd);
	write (fd, "\n", 1);
	printf("b: %c | %x\n\n", b, b);
	b <<= 2;
	printf("b <<= 2;\n");
	ft_put_bin((void *)&b, fd);
	write (fd, "\n", 1);
	printf("b: %c | %x\n\n", b, b);
	b = ~b;
	printf("b = ~b;\n");
	ft_put_bin((void *)&b, fd);
	write (fd, "\n", 1);
	printf("b: %c | %x\n\n", b, b);
	u = 0xA1B2C3D4;
	x = &u;
	printf("u = 0xA1B2C3D4;\n");
	ft_put_hex(&u, 1);
	ft_put_hex((void *)&u + 1, 1);
	ft_put_hex((void *)&u + 2, 1);
	ft_put_hex((void *)&u + 3, 1);
	write (1, "\n", 1);
	b = *(unsigned char *)((void *)&u + 8);
	write (1, " ", 1);
	ft_put_bin((void *)&b, 1);
	b = *(unsigned char *)((void *)&u + 7);
	write (1, " ", 1);
	ft_put_bin((void *)&b, 1);
	b = *(unsigned char *)((void *)&u + 6);
	write (1, " ", 1);
	ft_put_bin((void *)&b, 1);
	b = *(unsigned char *)((void *)&u + 5);
	write (1, " ", 1);
	ft_put_bin((void *)&b, 1);
	b = *(unsigned char *)((void *)&u + 4);
	write (1, " ", 1);
	ft_put_bin((void *)&b, 1);
	b = *(unsigned char *)((void *)&u + 3);
	write (1, " ", 1);
	ft_put_bin((void *)&b, 1);
	write (1, " ", 1);
	b = *(unsigned char *)((void *)&u + 2);
	ft_put_bin((void *)&b, 1);
	write (1, " ", 1);
	b = *(unsigned char *)((void *)&u + 1);
	ft_put_bin((void *)&b, 1);
	write (1, " ", 1);
	b = *(unsigned char *)&u;
	ft_put_bin((void *)&b, 1);
	write (1, "\n", 1);
	printf("u: %X, &=%p\n", u, ((void *)&u + 0));
	printf("u: %X, &=%p\n", *(unsigned int *)((void *)&u + 4), ((void *)&u + 4));
	printf("u: %X, &=%p\n", *(unsigned int *)((void *)&u + 8), ((void *)&u + 8));
	printf("u: %X, &=%p\n", *(unsigned int *)((void *)&u + 12), ((void *)&u + 12));
	printf("u: %X, &=%p\n", *(unsigned int *)((void *)&u + 16), ((void *)&u + 16));
	printf("u: %X, &=%p\n", *(unsigned int *)((void *)&u + 20), ((void *)&u + 20));
	printf("u: %.8X, &=%p\n", *(unsigned int *)((void *)&u + 24), ((void *)&u + 24));
	printf("u: %.8X, &=%p\n", *(unsigned int *)((void *)&u + 28), ((void *)&u + 28));
	printf("u: %.8X, &=%p\n", *(unsigned int *)((void *)&u + 32), ((void *)&u + 32));
	printf("u: %.8X, &=%p\n", *(unsigned int *)((void *)&u + 36), ((void *)&u + 36));
	printf("u: %.8X, &=%p\n", *(unsigned int *)((void *)&u + 40), ((void *)&u + 40));
	printf("u: %.8X, &=%p\n", *(unsigned int *)((void *)&u + 44), ((void *)&u + 44));
	printf("u: %.8X, &=%p\n", *(unsigned int *)((void *)&u + 210), ((void *)&u + 210));
	l = 0;
	b = 0;
	while (l < 40000000)
	{
		write(1, &s[0 + l], 1);
		l++;	
	}
	c = ft_print_memory((void *)((void *)&s[0] - 12000), 1, 18000);
	return (0);
}
/*
OTHER STUFF

	unsigned char	*s2;
	void			*c;
	s2 = malloc((long)4000000001);
	s2[30000] = '9';
	s2[300000] = 'a';
	s2[3000000] = 'b';
	s2[30000000] = 'c';
	s2[300000000] = 'd';
	s2[3000000000] = 'e';
	c = ft_print_memory_2(&s2[0], 1, (unsigned int)4000000000);


�3kH~9x86_64./a.outSYSTEMD_EXEC_PID=22833SSH_AUTH_SOCK=/run/user/101114/keyring/sshSESSION_MANAGER=local/c1r9s3.42prague.com:@/tmp/.ICE-unix/22833,unix/c1r9s3.42prague.com:/tmp/.ICE-unix/22833GNOME_TERMINAL_SCREEN=/org/gnome/Terminal/screen/288dc5b2_cea6_410b_9fb6_0253f77c8774LANG=en_US.UTF-8XDG_CURRENT_DESKTOP=ubuntu:GNOMEPWD=/nfs/homes/okraus/42core/x_bitwise_arrays_endian/42-x-miscellaneousXDG_GREETER_DATA_DIR=/var/lib/lightdm-data/okrausLIBVIRT_DEFAULT_URI=qemu:///systemGPG_AGENT_INFO=/run/user/101114/gnupg/S.gpg-agent:0:1DESKTOP_SESSION=ubuntuQT_IM_MODULE=ibusXDG_MENU_PREFIX=gnome-XDG_SESSION_PATH=/org/freedesktop/DisplayManager/Session0USER=okrausDBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/101114/bus,guid=f1e58eebaa33efbcaaa4d7b063fa16cdDOCKER_HOST=unix:///run/user/101114/docker.sockSSH_AGENT_LAUNCHER=gnome-keyringGTK_MODULES=gail:atk-bridgeXDG_CONFIG_DIRS=/etc/xdg/xdg-ubuntu:/etc/xdgVTE_VERSION=6800XDG_SESSION_DESKTOP=ubuntuQT_ACCESSIBILITY=1GNOME_DESKTOP_SESSION_ID=this-is-deprecatedKRB5CCNAME=FILE:/tmp/krb5cc_101114_0ztNK0LOGNAME=okrausGNOME_TERMINAL_SERVICE=:1.112PATH=/nfs/homes/okraus/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/binXDG_RUNTIME_DIR=/run/user/101114XDG_DATA_DIRS=/usr/share/ubuntu:/usr/share/gnome:/nfs/homes/okraus/.local/share/flatpak/exports/share:/var/lib/flatpak/exports/share:/usr/local/share:/usr/share:/var/lib/snapd/desktopXDG_SEAT_PATH=/org/freedesktop/DisplayManager/Seat0SHELL=/bin/zshXMODIFIERS=@im=ibusDBUS_STARTER_BUS_TYPE=sessionHOME=/nfs/homes/okrausXDG_SESSION_TYPE=x11COLORTERM=truecolorXAUTHORITY=/nfs/homes/okraus/.XauthorityDBUS_STARTER_ADDRESS=unix:path=/run/user/101114/bus,guid=f1e58eebaa33efbcaaa4d7b063fa16cdDISPLAY=:0TERM=xterm-256colorGDMSESSION=ubuntuXDG_SESSION_CLASS=userSHLVL=1OLDPWD=/nfs/homes/okraus/42core/x_bitwise_arrays_endian/42-x-miscellaneous_=/nfs/homes/okraus/42core/x_bitwise_arrays_endian/42-x-miscellaneous/./a.out./a.out00007ffe1f4f7410: 0000 0000 0000 0000 0000 0000 0000 0000 ................
*/
