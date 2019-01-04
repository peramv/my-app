#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_process_code : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_process_code() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_process_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_PROCESS_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The %TRANSTYPE% record for the same %FUNDNAME% %CLASSNAME% and Effective Date %EFFECDATE% already exists.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The %TRANSTYPE% record for the same %FUNDNAME% %CLASSNAME% and Effective Date %EFFECDATE% already exists.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der %TRANSTYPE%– Eintrag für den selben %FUNDNAME%  %CLASSNAME%und Effektivdatum %EFFECDATE% existiert bereits.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El registro %TRANSTYPE% para el mismo %FUNDNAME% %CLASSNAME% y la fecha de entrada en vigencia %EFFECDATE% ya existe.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement %TRANSTYPE% pour les mêmes fonds %FUNDNAME% et classe %CLASSNAME% et pour la date d'entrée en vigueur %EFFECDATE% existe déjà.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het record %TRANSTYPE% voor dezelfde %FUNDNAME% %CLASSNAME% en ingangsdatum %EFFECDATE% bestaat al")); }

        // Actions
	};
}



