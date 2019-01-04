#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_fund_not_authorized : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_fund_not_authorized() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_fund_not_authorized() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_FUND_NOT_AUTHORIZED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cannot delete owner account entity unless adding another owner.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Cannot delete owner account entity unless adding another owner.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Eigentümer-Konto-Objekt kann nicht gelöscht werden, wenn kein weiterer Eigentümer hinzugefügt wird.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se puede eliminar la entidad de cuenta propietaria a menos que se añada otro propietario.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de supprimer l'entité du titulaire du compte à moins d'ajouter un autre titulaire.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Eigenaar accounteenheid kan alleen worden gewist als er een andere eigenaar wordt toegevoegd")); }

        // Actions
	};
}



