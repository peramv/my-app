#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_wire_order_num_must_be_numeric : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_wire_order_num_must_be_numeric() { }
		~CIFast_Infrastructure_ifastcbo_err_wire_order_num_must_be_numeric() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WIRE_ORDER_NUM_MUST_BE_NUMERIC")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Error reading bin file %FILE%. Expected to read %EXPECTED% bytes at offset %OFFSET%, but only was able to read %RECEIVED% bytes.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Error reading bin file %FILE%. Expected to read %EXPECTED% bytes at offset %OFFSET%, but only was able to read %RECEIVED% bytes.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fehler beim Lesen von bin-Datei %FILE%. %EXPECTED% Byte sollten vom Offset %OFFSET% gelesen werden, aber nur %RECEIVED% Byte wurden gelesen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Error al leer el archivo binario %FILE%. Se esperaba leer %EXPECTED% bytes en el offset %OFFSET%, pero sólo se pudieron leer %RECEIVED% bytes.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur lors de la lecture du fichier BIN %FILE%. La lecture de %EXPECTED% multiplets était escomptée en compensation %OFFSET%, mais seule la lecture de %RECEIVED% multiplets a été possible.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fout bij lezen binair bestand %FILE%. Verwachtte %EXPECTED% bytes te lezen bij offset %OFFSET%, maar kon alleen %RECEIVED% bytes lezen")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check bin file for corruption.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Check bin file for corruption.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie, ob die bin-Datei beschädigt ist.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Check bin file for corruption.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le fichier BIN pour la corruption.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer of het binaire bestand beschadigd is")); }
	};
}



