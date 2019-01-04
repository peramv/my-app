#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_crud_code : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_crud_code() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_crud_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_CRUD_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Spousal Entity contributor should be setup and only one entry is allowed.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Spousal Entity contributor should be setup and only one entry is allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ehepartner-Objektanleger sollte erstellt und nur ein Eintrag ist zugelassen sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe configurarse la entidad Aportante conyugal y sólo se permite una entrada")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le conjoint cotisant doit être créé; un seul conjoint cotisant est autorisé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bijdrager echtelijke eenheid moet worden ingesteld en er is slechts één invoer toegestaan")); }

        // Actions
	};
}



