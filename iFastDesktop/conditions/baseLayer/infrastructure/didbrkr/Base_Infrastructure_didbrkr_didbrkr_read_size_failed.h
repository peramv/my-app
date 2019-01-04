#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_didbrkr_didbrkr_read_size_failed : public CConditionObject
	{
	public:
		CBase_Infrastructure_didbrkr_didbrkr_read_size_failed() { }
		~CBase_Infrastructure_didbrkr_didbrkr_read_size_failed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_READ_SIZE_FAILED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

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



