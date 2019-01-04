#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_paf_bucket : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_paf_bucket() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_paf_bucket() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_PAF_BUCKET")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transaction already exists. Duplicate transaction number is not allowed.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Transaction already exists. Duplicate transaction number is not allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Transaktion existiert bereits. Eine doppelte Transaktionsnummer ist nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La transacción ya existe. No se permite un número de transacción repetido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Transaction déjà existante.  La copie du numéro de transaction n'est pas autorisée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Transactie bestaat al. Dubbel transactienummer is niet toegestaan")); }

        // Actions
	};
}



