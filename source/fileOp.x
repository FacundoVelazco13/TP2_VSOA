struct write_parameters
{
	char token[32];
	char contenido[32];
};

program fileOp{
	version version1 {
		int escribir(write_parameters) = 1;
	} = 1;
}=0x1;