ENTRY(reset_handler)
/*
メモリ空間の定義
https://qiita.com/mitazet/items/83ddd6cdffc43dd42f21
 */
MEMORY
{
	FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 128K
}
/*
セクションの定義．
メモリ空間の配置
*/
SECTIONS
{
	.text :
	{
		KEEP(*(.isr_vector)) /* KEEPは入力がなくても出力する */
		*(.text) /*  */
	} >FLASH /* FLASH領域にこれを配置する */
}
