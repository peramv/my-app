#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_fid_account : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_fid_account() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_fid_account() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_FID_ACCOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Batch Name cannot be blank.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Batch Name cannot be blank.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Batch-Name darf nicht leer sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El nombre de lote no puede estar en blanco")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ Nom du lot doit être rempli.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Batchnaam kan niet leeg zijn")); }

        // Actions
	};
}



