#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_invalid_operation_authority_2 : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_invalid_operation_authority_2() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_invalid_operation_authority_2() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_INVALID_OPERATION_AUTHORITY_2")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Request failed due to corresponding Remarks record not found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Request failed due to corresponding Remarks record not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Anfrage fehlgeschlagen, da der entsprechende Kommentar-Eintrag nicht gefunden wurde.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Falló la solicitud debido a que no se encontró el registro de  comentarios correspondiente")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La requête a échoué car l'enregistrement de remarque correspondant est introuvable.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Opdracht is mislukt omdat het bijbehorende opmerkingenrecord niet is gevonden")); }

        // Actions
	};
}



