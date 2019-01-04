#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_city_not_apo_fpo : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_city_not_apo_fpo() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_city_not_apo_fpo() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_CITY_NOT_APO_FPO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Nominee Owner Entity must be setup and only one entry is allowed.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Nominee Owner Entity must be setup and only one entry is allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bevollmächtigter Eigentümer-Objekt sollte erstellt und nur ein Eintrag zugelassen sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe configurarse la entidad Propietario nominatario y sólo se permite una entrada")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le titulaire nominé doit être créé; un seul titulaire nominé est autorisé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Eenheid gemachtigde eigenaar moet worden ingesteld en er is slechts één invoer toegestaan")); }

        // Actions
	};
}



