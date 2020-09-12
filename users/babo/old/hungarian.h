#pragma once

enum unicode_names {
    A_AC,
    E_AC,
    I_AC,
    O_AC,
    O_DA,
    O_DI,
    U_AC,
    U_DA,
    U_DI,
    a_AC,
    e_AC,
    i_AC,
    o_AC,
    o_DA,
    o_DI,
    u_AC,
    u_DA,
    u_DI,
};

// 00C1	Á	00E1	á	A acute
// 00C9	É	00E9	é	E acute
// 00D6	Ö	00F6	ö	O diaeresis
// 00D3	Ó	00F3	ó	O acute
// 0150	Ő	0151	ő	O double acute
// 00CD	Í	00ED	í	I acute
// 00DC	Ü	00FC	ü	U diaeresis
// 00DA	Ú	00FA	ú	U acute
// 0170	Ű	0171	ű	U double acute

const uint32_t PROGMEM unicode_map[] = {
    [A_AC] = 0x00C1,
    [E_AC] = 0x00C9,
    [I_AC] = 0x00ED,
    [O_AC] = 0x00D3,
    [O_DA] = 0x0150,
    [O_DI] = 0x00D6,
    [U_AC] = 0x00DA,
    [U_DA] = 0x0170,
    [U_DI] = 0x00DC,

    [a_AC] = 0x00E1,
    [e_AC] = 0x00E9,
    [i_AC] = 0x00ED,
    [o_AC] = 0x00F3,
    [o_DA] = 0x0151,
    [o_DI] = 0x00F6,
    [u_AC] = 0x00FA,
    [u_DA] = 0x0171,
    [u_DI] = 0x00FC,
};

#define AAC XP(a_AC, A_AC)
#define EAC XP(e_AC, E_AC)
#define IAC XP(i_AC, I_AC)
#define OAC XP(o_AC, O_AC)
#define ODA XP(o_DA, O_DA)
#define ODI XP(o_DI, O_DI)
#define UAC XP(u_AC, U_AC)
#define UDA XP(u_DA, U_DA)
#define UDI XP(u_DI, U_DI)