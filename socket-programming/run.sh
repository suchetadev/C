rm oserver oclient
gcc -o oserver server.c
gcc -o oclient client.c
rm oadd_server
rm osub_server
rm omul_server
rm odiv_server
gcc -o oadd_server add_server.c
gcc -o osub_server sub_server.c
gcc -o omul_server mul_server.c
gcc -o odiv_server div_server.c
./oserver
