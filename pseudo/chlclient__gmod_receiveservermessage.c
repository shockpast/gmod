/* 
client.dylib

int __cdecl CHLClient::GMOD_ReceiveServerMessage(CHLClient *this, bf_read *a2, bf_read *a3)
{
  bf_read *v3; // esi
  int v4; // ebx
  int result; // eax
  bf_read **v6; // ecx
  _DWORD *v7; // esi
  int v8; // eax
  int v9; // eax
  _DWORD *v10; // esi
  int v11; // edx
  int v12; // ebx
  unsigned __int64 v13; // rt0
  int v14; // esi
  int v15; // esi
  bool v16; // zf
  unsigned __int64 v17; // rt0
  GModDataPack *v18; // eax
  int v19; // [esp+8h] [ebp-60h]
  char v20[24]; // [esp+20h] [ebp-48h] BYREF
  char v21[20]; // [esp+38h] [ebp-30h] BYREF
  _DWORD *v22; // [esp+4Ch] [ebp-1Ch]
  int v23; // [esp+50h] [ebp-18h]
  bf_read **v24; // [esp+54h] [ebp-14h]
  int v25; // [esp+58h] [ebp-10h]

  v3 = a2;
  v4 = 2439329;
  v25 = 2439329;
  result = *(a2 + 3);
  if ( *(a2 + 2) - result > 7 )
  {
    v24 = *(a2 + 2);
    v23 = result + 8;
    *(a2 + 3) = result + 8;
    v11 = *a2;
    LODWORD(v13) = *(*a2 + 4 * (result >> 5));
    HIDWORD(v13) = *(*a2 + 4 * ((result + 7) >> 5));
    v12 = v13 >> (result & 0x1F);
    switch ( v12 )
    {
      case 4:
        v14 = v23;
        if ( v24 - v23 > 15 )
        {
          *(a2 + 3) = result + 24;
          LODWORD(v17) = *(v11 + 4 * (v14 >> 5));
          HIDWORD(v17) = *(v11 + 4 * ((result + 23) >> 5));
          v15 = (v17 >> (v14 & 0x1F));
        }
        else
        {
          *(a2 + 3) = v24;
          bf_read::SetOverflowFlag(a2);
          v15 = 0;
        }
        if ( ((a3 >> 3) - 3) >= 0x10001 )
          return Msg(&algn_5F32FD[v25 + 2]);
        bf_read::ReadBytes(a2, &aFaceproxy[v25], (a3 >> 3) - 3);
        v18 = DataPack();
        return GModDataPack::UpdateFile(v18, v15, &aFaceproxy[v25], (a3 >> 3) - 3, 1);
      case 3:
        return result;
      case 1:
        return GarrysMod::AutoRefresh::ReceiveMessage(a2, a3, v19);
    }
    v16 = v12 == 0;
    v4 = v25;
    v3 = a2;
    if ( !v16 )
      return Msg(&aNotNetMessage[v25 - 2439329]);
  }
  else
  {
    *(a2 + 3) = *(a2 + 2);
    bf_read::SetOverflowFlag(a2);
  }
  if ( g_bLevelPostInitialized[v4 - 2439329] )
    ProcessOnDataChangedEvents();
  v6 = *(&g_NetIncoming_ptr + v4 - 2439329);
  result = *(&g_Lua_InNetMessage_ptr[-609833] + v4 + 3);
  *v6 = v3;
  v7 = *(&g_Lua_ptr + v4 - 2439329);
  *result = 1;
  if ( *v7 )
  {
    v24 = v6;
    v23 = result;
    CLuaObject::CLuaObject(v21);
    v8 = *v7;
    v22 = v7;
    v9 = (*(*v8 + 232))(v8);
    (*(*v9 + 80))(v9, v25 + 6143722, v21);
    if ( CLuaObject::isTable(v21) )
    {
      CLuaObject::CLuaObject(v20);
      CLuaObject::GetMember(v21, v25 + 6239038, v20);
      v10 = v22;
      if ( CLuaObject::isFunction(v20) )
      {
        CLuaObject::Push(v20);
        (*(**v10 + 120))(*v10, COERCE_UNSIGNED_INT64((a3 - 8)), HIDWORD(COERCE_UNSIGNED_INT64((a3 - 8))));
        (*(**v10 + 260))(*v10, 1);
      }
      CLuaObject::~CLuaObject(v20);
    }
    CLuaObject::~CLuaObject(v21);
    result = v23;
    v6 = v24;
  }
  *v6 = 0;
  *result = 0;
  return result;
}
*/

/* 
client.dll

// #STR: "Lua file %d too big, ignoring! (%lu > %lu)\n", "Not net message!?\n", "Incoming"
void __fastcall CHLClient::GMOD_ReceiveServerMessage(__int64 a1, __int64 a2, __int64 a3)
{
  __int64 v3; // rcx
  int v4; // ebp
  __int64 v5; // rbx
  unsigned int v6; // r8d
  __int64 v7; // r9
  unsigned int *v8; // rax
  unsigned int *v9; // rax
  unsigned int v10; // r11d
  __int64 v11; // rax
  unsigned int v12; // edx
  unsigned int v13; // esi
  int *v14; // rax
  int v15; // r8d
  unsigned int *v16; // rax
  int v17; // r9d
  unsigned int v18; // r11d
  int v19; // esi
  unsigned int v20; // ebp
  __int64 v21; // rax
  char v22[32]; // [rsp+30h] [rbp-48h] BYREF
  char v23[32]; // [rsp+50h] [rbp-28h] BYREF

  v3 = *(a2 + 28);
  v4 = a3;
  v5 = a2;
  if ( v3 < 8 )
  {
    v9 = *(a2 + 32);
    v7 = *(a2 + 24);
    v10 = 8 - v3;
    if ( v9 == *(a2 + 40) )
    {
      *(a2 + 28) = 1;
      *(a2 + 32) = v9 + 1;
      *(a2 + 8) = 1;
      *(a2 + 24) = 0;
    }
    else if ( v9 <= *(a2 + 40) )
    {
      a3 = *v9;
      *(a2 + 32) = v9 + 1;
      *(a2 + 24) = a3;
      if ( !*(a2 + 8) )
      {
        v12 = (a3 & dword_180791B70[v10]) << v3;
        v3 = v10;
        v7 = v12 | v7;
        a2 = 32 - v10;
        *(v5 + 28) = a2;
        a3 = a3 >> v10;
        goto LABEL_25;
      }
    }
    else
    {
      *(a2 + 8) = 1;
      *(a2 + 24) = 0;
    }
LABEL_14:
    if ( byte_18095A149 )
      sub_1801FFE90(v3, a2, a3, v7);
    byte_180903D3F = 1;
    qword_180918DA0 = v5;
    if ( g_Lua )
    {
      sub_1800AEE40(v23);
      v11 = (*(*g_Lua + 464i64))(g_Lua);
      (*(*v11 + 240i64))(v11, "net", v23);
      if ( sub_1800B11A0(v23) )
      {
        sub_1800AEE40(v22);
        sub_1800AF2E0(v23, "Incoming", v22);
        if ( sub_1800B1110(v22) )
        {
          CLuaObject::Push(v22);
          (*(*g_Lua + 240i64))(g_Lua);
          (*(*g_Lua + 520i64))(g_Lua, 1i64);
        }
        CLuaObject::destr_CLuaObject(v22);
      }
      CLuaObject::destr_CLuaObject(v23);
    }
    qword_180918DA0 = 0i64;
    byte_180903D3F = 0;
    return;
  }
  v6 = *(a2 + 24);
  a2 = (v3 - 8);
  v7 = v6;
  *(v5 + 28) = a2;
  if ( v3 == 8 )
  {
    v8 = *(v5 + 32);
    *(v5 + 28) = 32;
    if ( v8 == *(v5 + 40) )
    {
      *(v5 + 28) = 1;
      a3 = 0i64;
      *(v5 + 32) = v8 + 1;
      a2 = 1i64;
    }
    else
    {
      a2 = 32i64;
      if ( v8 <= *(v5 + 40) )
      {
        a3 = *v8;
        *(v5 + 32) = v8 + 1;
      }
      else
      {
        *(v5 + 8) = 1;
        a3 = 0i64;
      }
    }
  }
  else
  {
    a3 = v6 >> 8;
  }
LABEL_25:
  *(v5 + 24) = a3;
  if ( v7 == 1 )
  {
    sub_1800584B0(v5, v4);
    return;
  }
  if ( v7 != 3 )
  {
    if ( v7 == 4 )
    {
      if ( a2 < 16 )
      {
        v16 = *(v5 + 32);
        v17 = 16 - a2;
        if ( v16 == *(v5 + 40) )
        {
          *(v5 + 28) = 1;
          *(v5 + 32) = v16 + 1;
          v13 = 0;
          *(v5 + 8) = 1;
          *(v5 + 24) = 0;
        }
        else if ( v16 <= *(v5 + 40) )
        {
          v18 = *v16;
          *(v5 + 32) = v16 + 1;
          *(v5 + 24) = v18;
          if ( *(v5 + 8) )
          {
            v13 = 0;
          }
          else
          {
            v19 = v18 & dword_180791B70[v17];
            *(v5 + 28) = 32 - v17;
            v13 = a3 | (v19 << a2);
            *(v5 + 24) = v18 >> v17;
          }
        }
        else
        {
          *(v5 + 8) = 1;
          v13 = 0;
          *(v5 + 24) = 0;
        }
      }
      else
      {
        v13 = a3;
        *(v5 + 28) = a2 - 16;
        if ( a2 == 16 )
        {
          v14 = *(v5 + 32);
          *(v5 + 28) = 32;
          if ( v14 == *(v5 + 40) )
          {
            *(v5 + 28) = 1;
            *(v5 + 32) = v14 + 1;
            *(v5 + 24) = 0;
          }
          else if ( v14 <= *(v5 + 40) )
          {
            v15 = *v14;
            *(v5 + 32) = v14 + 1;
            *(v5 + 24) = v15;
          }
          else
          {
            *(v5 + 8) = 1;
            *(v5 + 24) = 0;
          }
        }
        else
        {
          *(v5 + 24) = WORD1(a3);
        }
      }
      v20 = (v4 >> 3) - 3;
      if ( v20 <= 0x10000 )
      {
        bf_read::ReadBytes(v5, &aFaceproxy, v20);
        v21 = DataPack();
        GModDataPack::UpdateFile(v21, v13, &aFaceproxy, v20, 1);
      }
      else
      {
        Msg("Lua file %d too big, ignoring! (%lu > %lu)\n", v13, v20, 0x10000i64);
      }
      return;
    }
    if ( v7 )
    {
      Msg("Not net message!?\n", a2);
      return;
    }
    goto LABEL_14;
  }
}
*/

// @note: more readable version of it, some places might be not correct, idc

void __fastcall CHLClient::GMOD_ReceiveServerMessage(CHLClient* this, bf_read* message, int length)
{
    unsigned int bit_buffer;       // current bit buffer
    unsigned int bit_count;        // number of bits remaining in buffer
    unsigned int message_type;     // message type (0, 1, 3, 4, etc.)
    unsigned int file_id;          // for message type 4 (Lua file updates)
    unsigned int file_size;        // length of incoming Lua file
    char lua_net_object[32];
    char lua_incoming_object[32]; 

    bit_count = message->m_nBitsLeft;
    if (bit_count < 8)
    {
        bf_read::ReadBits(message, 8 - bit_count);
    }

    message_type = bf_read::ReadUnsignedInt(message, 8);

    // Handle message type
    switch (message_type)
    {
        // auto refresh
        case 1:
            sub_1800584B0(message, length);
            return;

        // 
        case 3:
            return;

        // file download? transfer?
        case 4:
        {
            file_id = bf_read::ReadUnsignedInt(message, 16);
            file_size = (lengthBits >> 3) - 3;

            if (file_size > 0x10000)
            {
                Msg("Lua file %d too big, ignoring! (%lu > %lu)\n", file_id, file_size, 0x10000);
                return;
            }

            char buffer[65536];
            bf_read::ReadBytes(message, buffer, file_size);

            GModDataPack* pack = DataPack();
            GModDataPack::UpdateFile(pack, file_id, buffer, file_size, true);
            return;
        }

        // net.Send or net.Broadcast
        case 0:
        {
            byte_180903D3F = 1; // pretty sure it's g_NetIncoming
            qword_180918DA0 = (uintptr_t)message; // no idea, some local copy of message

            if (g_Lua)
            {
                // Lookup: net.Incoming in Lua
                CLuaObject netObj;
                g_Lua->GetGlobal("net", &netObj);

                if (netObj.IsTable())
                {
                    CLuaObject incomingFunc;
                    netObj.GetMember("Incoming", &incomingFunc);

                    if (incomingFunc.IsFunction())
                    {
                        incomingFunc.Push();
                        g_Lua->Call(1);
                    }

                    incomingFunc.~CLuaObject();
                }

                netObj.~CLuaObject();
            }

            qword_180918DA0 = 0; // no idea, some local copy of message
            byte_180903D3F = 0; // pretty sure it's g_NetIncoming
            return;
        }

        default:
            Msg("Not net message!?\n"); // funny message
            return;
    }
}