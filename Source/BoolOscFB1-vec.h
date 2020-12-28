/* ------------------------------------------------------------
author: "Till Bovermann"
name: "BoolOscFB1"
Code generated with Faust 2.28.8 (https://faust.grame.fr)
Compilation options: -lang cpp -vec -lv 0 -vs 32 -ftz 0 -mcd 16
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

#include <cmath>
#include <cstring>

// #include "faust/gui/MapUI.h"
/************************** BEGIN APIUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef API_UI_H
#define API_UI_H

#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <map>

/************************** BEGIN meta.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __meta__
#define __meta__

struct Meta
{
    virtual ~Meta() {};
    virtual void declare(const char* key, const char* value) = 0;
    
};

#endif
/**************************  END  meta.h **************************/
/************************** BEGIN UI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2020 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __UI_H__
#define __UI_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

/*******************************************************************************
 * UI : Faust DSP User Interface
 * User Interface as expected by the buildUserInterface() method of a DSP.
 * This abstract class contains only the method that the Faust compiler can
 * generate to describe a DSP user interface.
 ******************************************************************************/

struct Soundfile;

template <typename REAL>
struct UIReal
{
    UIReal() {}
    virtual ~UIReal() {}
    
    // -- widget's layouts
    
    virtual void openTabBox(const char* label) = 0;
    virtual void openHorizontalBox(const char* label) = 0;
    virtual void openVerticalBox(const char* label) = 0;
    virtual void closeBox() = 0;
    
    // -- active widgets
    
    virtual void addButton(const char* label, REAL* zone) = 0;
    virtual void addCheckButton(const char* label, REAL* zone) = 0;
    virtual void addVerticalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    virtual void addHorizontalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    virtual void addNumEntry(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    
    // -- passive widgets
    
    virtual void addHorizontalBargraph(const char* label, REAL* zone, REAL min, REAL max) = 0;
    virtual void addVerticalBargraph(const char* label, REAL* zone, REAL min, REAL max) = 0;
    
    // -- soundfiles
    
    virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) = 0;
    
    // -- metadata declarations
    
    virtual void declare(REAL* zone, const char* key, const char* val) {}
};

struct UI : public UIReal<FAUSTFLOAT>
{
    UI() {}
    virtual ~UI() {}
};

#endif
/**************************  END  UI.h **************************/
/************************** BEGIN PathBuilder.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef FAUST_PATHBUILDER_H
#define FAUST_PATHBUILDER_H

#include <vector>
#include <string>
#include <algorithm>

/*******************************************************************************
 * PathBuilder : Faust User Interface
 * Helper class to build complete hierarchical path for UI items.
 ******************************************************************************/

class PathBuilder
{

    protected:
    
        std::vector<std::string> fControlsLevel;
       
    public:
    
        PathBuilder() {}
        virtual ~PathBuilder() {}
    
        std::string buildPath(const std::string& label) 
        {
            std::string res = "/";
            for (size_t i = 0; i < fControlsLevel.size(); i++) {
                res += fControlsLevel[i];
                res += "/";
            }
            res += label;
            std::replace(res.begin(), res.end(), ' ', '_');
            return res;
        }
    
        std::string buildLabel(std::string label)
        {
            std::replace(label.begin(), label.end(), ' ', '_');
            return label;
        }
    
        void pushLabel(const std::string& label) { fControlsLevel.push_back(label); }
        void popLabel() { fControlsLevel.pop_back(); }
    
};

#endif  // FAUST_PATHBUILDER_H
/**************************  END  PathBuilder.h **************************/
/************************** BEGIN ValueConverter.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __ValueConverter__
#define __ValueConverter__

/***************************************************************************************
								ValueConverter.h
                            (GRAME, Copyright 2015-2019)

Set of conversion objects used to map user interface values (for example a gui slider
delivering values between 0 and 1) to faust values (for example a vslider between
20 and 20000) using a log scale.

-- Utilities

Range(lo,hi) : clip a value x between lo and hi
Interpolator(lo,hi,v1,v2) : Maps a value x between lo and hi to a value y between v1 and v2
Interpolator3pt(lo,mi,hi,v1,vm,v2) : Map values between lo mid hi to values between v1 vm v2

-- Value Converters

ValueConverter::ui2faust(x)
ValueConverter::faust2ui(x)

-- ValueConverters used for sliders depending of the scale

LinearValueConverter(umin, umax, fmin, fmax)
LinearValueConverter2(lo, mi, hi, v1, vm, v2) using 2 segments
LogValueConverter(umin, umax, fmin, fmax)
ExpValueConverter(umin, umax, fmin, fmax)

-- ValueConverters used for accelerometers based on 3 points

AccUpConverter(amin, amid, amax, fmin, fmid, fmax)		-- curve 0
AccDownConverter(amin, amid, amax, fmin, fmid, fmax)	-- curve 1
AccUpDownConverter(amin, amid, amax, fmin, fmid, fmax)	-- curve 2
AccDownUpConverter(amin, amid, amax, fmin, fmid, fmax)	-- curve 3

-- lists of ZoneControl are used to implement accelerometers metadata for each axes

ZoneControl(zone, valueConverter) : a zone with an accelerometer data converter

-- ZoneReader are used to implement screencolor metadata

ZoneReader(zone, valueConverter) : a zone with a data converter

****************************************************************************************/

#include <float.h>
#include <algorithm>    // std::max
#include <cmath>
#include <vector>
#include <assert.h>

//--------------------------------------------------------------------------------------
// Interpolator(lo,hi,v1,v2)
// Maps a value x between lo and hi to a value y between v1 and v2
// y = v1 + (x-lo)/(hi-lo)*(v2-v1)
// y = v1 + (x-lo) * coef   		with coef = (v2-v1)/(hi-lo)
// y = v1 + x*coef - lo*coef
// y = v1 - lo*coef + x*coef
// y = offset + x*coef				with offset = v1 - lo*coef
//--------------------------------------------------------------------------------------
class Interpolator
{
    private:

        //--------------------------------------------------------------------------------------
        // Range(lo,hi) clip a value between lo and hi
        //--------------------------------------------------------------------------------------
        struct Range
        {
            double fLo;
            double fHi;

            Range(double x, double y) : fLo(std::min<double>(x,y)), fHi(std::max<double>(x,y)) {}
            double operator()(double x) { return (x<fLo) ? fLo : (x>fHi) ? fHi : x; }
        };


        Range fRange;
        double fCoef;
        double fOffset;

    public:

        Interpolator(double lo, double hi, double v1, double v2) : fRange(lo,hi)
        {
            if (hi != lo) {
                // regular case
                fCoef = (v2-v1)/(hi-lo);
                fOffset = v1 - lo*fCoef;
            } else {
                // degenerate case, avoids division by zero
                fCoef = 0;
                fOffset = (v1+v2)/2;
            }
        }
        double operator()(double v)
        {
            double x = fRange(v);
            return  fOffset + x*fCoef;
        }

        void getLowHigh(double& amin, double& amax)
        {
            amin = fRange.fLo;
            amax = fRange.fHi;
        }
};

//--------------------------------------------------------------------------------------
// Interpolator3pt(lo,mi,hi,v1,vm,v2)
// Map values between lo mid hi to values between v1 vm v2
//--------------------------------------------------------------------------------------
class Interpolator3pt
{

    private:

        Interpolator fSegment1;
        Interpolator fSegment2;
        double fMid;

    public:

        Interpolator3pt(double lo, double mi, double hi, double v1, double vm, double v2) :
            fSegment1(lo, mi, v1, vm),
            fSegment2(mi, hi, vm, v2),
            fMid(mi) {}
        double operator()(double x) { return  (x < fMid) ? fSegment1(x) : fSegment2(x); }

        void getMappingValues(double& amin, double& amid, double& amax)
        {
            fSegment1.getLowHigh(amin, amid);
            fSegment2.getLowHigh(amid, amax);
        }
};

//--------------------------------------------------------------------------------------
// Abstract ValueConverter class. Converts values between UI and Faust representations
//--------------------------------------------------------------------------------------
class ValueConverter // Identity by default
{

    public:

        virtual ~ValueConverter() {}
        virtual double ui2faust(double x) { return x; };
        virtual double faust2ui(double x) { return x; };
};

//--------------------------------------------------------------------------------------
// A converter than can be updated
//--------------------------------------------------------------------------------------

class UpdatableValueConverter : public ValueConverter {
    
    protected:
        
        bool fActive;
        
    public:
        
        UpdatableValueConverter():fActive(true)
        {}
        virtual ~UpdatableValueConverter()
        {}
        
        virtual void setMappingValues(double amin, double amid, double amax, double min, double init, double max) = 0;
        virtual void getMappingValues(double& amin, double& amid, double& amax) = 0;
        
        void setActive(bool on_off) { fActive = on_off; }
        bool getActive() { return fActive; }
    
};

//--------------------------------------------------------------------------------------
// Linear conversion between ui and Faust values
//--------------------------------------------------------------------------------------
class LinearValueConverter : public ValueConverter
{
    
    private:
        
        Interpolator fUI2F;
        Interpolator fF2UI;
        
    public:
        
        LinearValueConverter(double umin, double umax, double fmin, double fmax) :
            fUI2F(umin,umax,fmin,fmax), fF2UI(fmin,fmax,umin,umax)
        {}
        
        LinearValueConverter() : fUI2F(0.,0.,0.,0.), fF2UI(0.,0.,0.,0.)
        {}
        virtual double ui2faust(double x) { return fUI2F(x); }
        virtual double faust2ui(double x) { return fF2UI(x); }
    
};

//--------------------------------------------------------------------------------------
// Two segments linear conversion between ui and Faust values
//--------------------------------------------------------------------------------------
class LinearValueConverter2 : public UpdatableValueConverter
{
    
    private:
    
        Interpolator3pt fUI2F;
        Interpolator3pt fF2UI;
        
    public:
    
        LinearValueConverter2(double amin, double amid, double amax, double min, double init, double max) :
            fUI2F(amin, amid, amax, min, init, max), fF2UI(min, init, max, amin, amid, amax)
        {}
        
        LinearValueConverter2() : fUI2F(0.,0.,0.,0.,0.,0.), fF2UI(0.,0.,0.,0.,0.,0.)
        {}
    
        virtual double ui2faust(double x) { return fUI2F(x); }
        virtual double faust2ui(double x) { return fF2UI(x); }
    
        virtual void setMappingValues(double amin, double amid, double amax, double min, double init, double max)
        {
            fUI2F = Interpolator3pt(amin, amid, amax, min, init, max);
            fF2UI = Interpolator3pt(min, init, max, amin, amid, amax);
        }

        virtual void getMappingValues(double& amin, double& amid, double& amax)
        {
            fUI2F.getMappingValues(amin, amid, amax);
        }
    
};

//--------------------------------------------------------------------------------------
// Logarithmic conversion between ui and Faust values
//--------------------------------------------------------------------------------------
class LogValueConverter : public LinearValueConverter
{

    public:

        LogValueConverter(double umin, double umax, double fmin, double fmax) :
            LinearValueConverter(umin, umax, std::log(std::max<double>(DBL_MIN, fmin)), std::log(std::max<double>(DBL_MIN, fmax)))
        {}

        virtual double ui2faust(double x) { return std::exp(LinearValueConverter::ui2faust(x)); }
        virtual double faust2ui(double x) { return LinearValueConverter::faust2ui(std::log(std::max<double>(x, DBL_MIN))); }

};

//--------------------------------------------------------------------------------------
// Exponential conversion between ui and Faust values
//--------------------------------------------------------------------------------------
class ExpValueConverter : public LinearValueConverter
{

    public:

        ExpValueConverter(double umin, double umax, double fmin, double fmax) :
            LinearValueConverter(umin, umax, std::min<double>(DBL_MAX, std::exp(fmin)), std::min<double>(DBL_MAX, std::exp(fmax)))
        {}

        virtual double ui2faust(double x) { return std::log(LinearValueConverter::ui2faust(x)); }
        virtual double faust2ui(double x) { return LinearValueConverter::faust2ui(std::min<double>(DBL_MAX, std::exp(x))); }

};

//--------------------------------------------------------------------------------------
// Convert accelerometer or gyroscope values to Faust values
// Using an Up curve (curve 0)
//--------------------------------------------------------------------------------------
class AccUpConverter : public UpdatableValueConverter
{

    private:

        Interpolator3pt fA2F;
        Interpolator3pt fF2A;

    public:

        AccUpConverter(double amin, double amid, double amax, double fmin, double fmid, double fmax) :
            fA2F(amin,amid,amax,fmin,fmid,fmax),
            fF2A(fmin,fmid,fmax,amin,amid,amax)
        {}

        virtual double ui2faust(double x) { return fA2F(x); }
        virtual double faust2ui(double x) { return fF2A(x); }

        virtual void setMappingValues(double amin, double amid, double amax, double fmin, double fmid, double fmax)
        {
            //__android_log_print(ANDROID_LOG_ERROR, "Faust", "AccUpConverter update %f %f %f %f %f %f", amin,amid,amax,fmin,fmid,fmax);
            fA2F = Interpolator3pt(amin, amid, amax, fmin, fmid, fmax);
            fF2A = Interpolator3pt(fmin, fmid, fmax, amin, amid, amax);
        }

        virtual void getMappingValues(double& amin, double& amid, double& amax)
        {
            fA2F.getMappingValues(amin, amid, amax);
        }

};

//--------------------------------------------------------------------------------------
// Convert accelerometer or gyroscope values to Faust values
// Using a Down curve (curve 1)
//--------------------------------------------------------------------------------------
class AccDownConverter : public UpdatableValueConverter
{

    private:

        Interpolator3pt	fA2F;
        Interpolator3pt	fF2A;

    public:

        AccDownConverter(double amin, double amid, double amax, double fmin, double fmid, double fmax) :
            fA2F(amin,amid,amax,fmax,fmid,fmin),
            fF2A(fmin,fmid,fmax,amax,amid,amin)
        {}

        virtual double ui2faust(double x) { return fA2F(x); }
        virtual double faust2ui(double x) { return fF2A(x); }

        virtual void setMappingValues(double amin, double amid, double amax, double fmin, double fmid, double fmax)
        {
             //__android_log_print(ANDROID_LOG_ERROR, "Faust", "AccDownConverter update %f %f %f %f %f %f", amin,amid,amax,fmin,fmid,fmax);
            fA2F = Interpolator3pt(amin, amid, amax, fmax, fmid, fmin);
            fF2A = Interpolator3pt(fmin, fmid, fmax, amax, amid, amin);
        }

        virtual void getMappingValues(double& amin, double& amid, double& amax)
        {
            fA2F.getMappingValues(amin, amid, amax);
        }
};

//--------------------------------------------------------------------------------------
// Convert accelerometer or gyroscope values to Faust values
// Using an Up-Down curve (curve 2)
//--------------------------------------------------------------------------------------
class AccUpDownConverter : public UpdatableValueConverter
{

    private:

        Interpolator3pt	fA2F;
        Interpolator fF2A;

    public:

        AccUpDownConverter(double amin, double amid, double amax, double fmin, double fmid, double fmax) :
            fA2F(amin,amid,amax,fmin,fmax,fmin),
            fF2A(fmin,fmax,amin,amax)				// Special, pseudo inverse of a non monotonic function
        {}

        virtual double ui2faust(double x) { return fA2F(x); }
        virtual double faust2ui(double x) { return fF2A(x); }

        virtual void setMappingValues(double amin, double amid, double amax, double fmin, double fmid, double fmax)
        {
            //__android_log_print(ANDROID_LOG_ERROR, "Faust", "AccUpDownConverter update %f %f %f %f %f %f", amin,amid,amax,fmin,fmid,fmax);
            fA2F = Interpolator3pt(amin, amid, amax, fmin, fmax, fmin);
            fF2A = Interpolator(fmin, fmax, amin, amax);
        }

        virtual void getMappingValues(double& amin, double& amid, double& amax)
        {
            fA2F.getMappingValues(amin, amid, amax);
        }
};

//--------------------------------------------------------------------------------------
// Convert accelerometer or gyroscope values to Faust values
// Using a Down-Up curve (curve 3)
//--------------------------------------------------------------------------------------
class AccDownUpConverter : public UpdatableValueConverter
{

    private:

        Interpolator3pt	fA2F;
        Interpolator fF2A;

    public:

        AccDownUpConverter(double amin, double amid, double amax, double fmin, double fmid, double fmax) :
            fA2F(amin,amid,amax,fmax,fmin,fmax),
            fF2A(fmin,fmax,amin,amax)				// Special, pseudo inverse of a non monotonic function
        {}

        virtual double ui2faust(double x) { return fA2F(x); }
        virtual double faust2ui(double x) { return fF2A(x); }

        virtual void setMappingValues(double amin, double amid, double amax, double fmin, double fmid, double fmax)
        {
            //__android_log_print(ANDROID_LOG_ERROR, "Faust", "AccDownUpConverter update %f %f %f %f %f %f", amin,amid,amax,fmin,fmid,fmax);
            fA2F = Interpolator3pt(amin, amid, amax, fmax, fmin, fmax);
            fF2A = Interpolator(fmin, fmax, amin, amax);
        }

        virtual void getMappingValues(double& amin, double& amid, double& amax)
        {
            fA2F.getMappingValues(amin, amid, amax);
        }
};

//--------------------------------------------------------------------------------------
// Base class for ZoneControl
//--------------------------------------------------------------------------------------
class ZoneControl
{

    protected:

        FAUSTFLOAT*	fZone;

    public:

        ZoneControl(FAUSTFLOAT* zone) : fZone(zone) {}
        virtual ~ZoneControl() {}

        virtual void update(double v) const {}

        virtual void setMappingValues(int curve, double amin, double amid, double amax, double min, double init, double max) {}
        virtual void getMappingValues(double& amin, double& amid, double& amax) {}

        FAUSTFLOAT* getZone() { return fZone; }

        virtual void setActive(bool on_off) {}
        virtual bool getActive() { return false; }

        virtual int getCurve() { return -1; }

};

//--------------------------------------------------------------------------------------
//  Useful to implement accelerometers metadata as a list of ZoneControl for each axes
//--------------------------------------------------------------------------------------
class ConverterZoneControl : public ZoneControl
{

    protected:

        ValueConverter* fValueConverter;

    public:

        ConverterZoneControl(FAUSTFLOAT* zone, ValueConverter* converter) : ZoneControl(zone), fValueConverter(converter) {}
        virtual ~ConverterZoneControl() { delete fValueConverter; } // Assuming fValueConverter is not kept elsewhere...

        virtual void update(double v) const { *fZone = fValueConverter->ui2faust(v); }

        ValueConverter* getConverter() { return fValueConverter; }

};

//--------------------------------------------------------------------------------------
// Association of a zone and a four value converter, each one for each possible curve.
// Useful to implement accelerometers metadata as a list of ZoneControl for each axes
//--------------------------------------------------------------------------------------
class CurveZoneControl : public ZoneControl
{

    private:

        std::vector<UpdatableValueConverter*> fValueConverters;
        int fCurve;

    public:

        CurveZoneControl(FAUSTFLOAT* zone, int curve, double amin, double amid, double amax, double min, double init, double max) : ZoneControl(zone), fCurve(0)
        {
            assert(curve >= 0 && curve <= 3);
            fValueConverters.push_back(new AccUpConverter(amin, amid, amax, min, init, max));
            fValueConverters.push_back(new AccDownConverter(amin, amid, amax, min, init, max));
            fValueConverters.push_back(new AccUpDownConverter(amin, amid, amax, min, init, max));
            fValueConverters.push_back(new AccDownUpConverter(amin, amid, amax, min, init, max));
            fCurve = curve;
        }
        virtual ~CurveZoneControl()
        {
            std::vector<UpdatableValueConverter*>::iterator it;
            for (it = fValueConverters.begin(); it != fValueConverters.end(); it++) {
                delete(*it);
            }
        }
        void update(double v) const { if (fValueConverters[fCurve]->getActive()) *fZone = fValueConverters[fCurve]->ui2faust(v); }

        void setMappingValues(int curve, double amin, double amid, double amax, double min, double init, double max)
        {
            fValueConverters[curve]->setMappingValues(amin, amid, amax, min, init, max);
            fCurve = curve;
        }

        void getMappingValues(double& amin, double& amid, double& amax)
        {
            fValueConverters[fCurve]->getMappingValues(amin, amid, amax);
        }

        void setActive(bool on_off)
        {
            std::vector<UpdatableValueConverter*>::iterator it;
            for (it = fValueConverters.begin(); it != fValueConverters.end(); it++) {
                (*it)->setActive(on_off);
            }
        }

        int getCurve() { return fCurve; }
};

class ZoneReader
{

    private:

        FAUSTFLOAT* fZone;
        Interpolator fInterpolator;

    public:

        ZoneReader(FAUSTFLOAT* zone, double lo, double hi) : fZone(zone), fInterpolator(lo, hi, 0, 255) {}

        virtual ~ZoneReader() {}

        int getValue()
        {
            return (fZone != nullptr) ? int(fInterpolator(*fZone)) : 127;
        }

};

#endif
/**************************  END  ValueConverter.h **************************/

class APIUI : public PathBuilder, public Meta, public UI
{
    public:
    
        enum ItemType { kButton = 0, kCheckButton, kVSlider, kHSlider, kNumEntry, kHBargraph, kVBargraph };
  
    protected:
    
        enum { kLin = 0, kLog = 1, kExp = 2 };
    
        int fNumParameters;
        std::vector<std::string> fPaths;
        std::vector<std::string> fLabels;
        std::map<std::string, int> fPathMap;
        std::map<std::string, int> fLabelMap;
        std::vector<ValueConverter*> fConversion;
        std::vector<FAUSTFLOAT*> fZone;
        std::vector<FAUSTFLOAT> fInit;
        std::vector<FAUSTFLOAT> fMin;
        std::vector<FAUSTFLOAT> fMax;
        std::vector<FAUSTFLOAT> fStep;
        std::vector<ItemType> fItemType;
        std::vector<std::map<std::string, std::string> > fMetaData;
        std::vector<ZoneControl*> fAcc[3];
        std::vector<ZoneControl*> fGyr[3];

        // Screen color control
        // "...[screencolor:red]..." etc.
        bool fHasScreenControl;      // true if control screen color metadata
        ZoneReader* fRedReader;
        ZoneReader* fGreenReader;
        ZoneReader* fBlueReader;

        // Current values controlled by metadata
        std::string fCurrentUnit;
        int fCurrentScale;
        std::string fCurrentAcc;
        std::string fCurrentGyr;
        std::string fCurrentColor;
        std::string fCurrentTooltip;
        std::map<std::string, std::string> fCurrentMetadata;
    
        // Add a generic parameter
        virtual void addParameter(const char* label,
                                FAUSTFLOAT* zone,
                                FAUSTFLOAT init,
                                FAUSTFLOAT min,
                                FAUSTFLOAT max,
                                FAUSTFLOAT step,
                                ItemType type)
        {
            std::string path = buildPath(label);
            fPathMap[path] = fLabelMap[label] = fNumParameters++;
            fPaths.push_back(path);
            fLabels.push_back(label);
            fZone.push_back(zone);
            fInit.push_back(init);
            fMin.push_back(min);
            fMax.push_back(max);
            fStep.push_back(step);
            fItemType.push_back(type);
            
            // handle scale metadata
            switch (fCurrentScale) {
                case kLin:
                    fConversion.push_back(new LinearValueConverter(0, 1, min, max));
                    break;
                case kLog:
                    fConversion.push_back(new LogValueConverter(0, 1, min, max));
                    break;
                case kExp: fConversion.push_back(new ExpValueConverter(0, 1, min, max));
                    break;
            }
            fCurrentScale = kLin;
            
            if (fCurrentAcc.size() > 0 && fCurrentGyr.size() > 0) {
                std::cerr << "warning : 'acc' and 'gyr' metadata used for the same " << label << " parameter !!\n";
            }

            // handle acc metadata "...[acc : <axe> <curve> <amin> <amid> <amax>]..."
            if (fCurrentAcc.size() > 0) {
                std::istringstream iss(fCurrentAcc);
                int axe, curve;
                double amin, amid, amax;
                iss >> axe >> curve >> amin >> amid >> amax;

                if ((0 <= axe) && (axe < 3) &&
                    (0 <= curve) && (curve < 4) &&
                    (amin < amax) && (amin <= amid) && (amid <= amax))
                {
                    fAcc[axe].push_back(new CurveZoneControl(zone, curve, amin, amid, amax, min, init, max));
                } else {
                    std::cerr << "incorrect acc metadata : " << fCurrentAcc << std::endl;
                }
                fCurrentAcc = "";
            }
       
            // handle gyr metadata "...[gyr : <axe> <curve> <amin> <amid> <amax>]..."
            if (fCurrentGyr.size() > 0) {
                std::istringstream iss(fCurrentGyr);
                int axe, curve;
                double amin, amid, amax;
                iss >> axe >> curve >> amin >> amid >> amax;

                if ((0 <= axe) && (axe < 3) &&
                    (0 <= curve) && (curve < 4) &&
                    (amin < amax) && (amin <= amid) && (amid <= amax))
                {
                    fGyr[axe].push_back(new CurveZoneControl(zone, curve, amin, amid, amax, min, init, max));
                } else {
                    std::cerr << "incorrect gyr metadata : " << fCurrentGyr << std::endl;
                }
                fCurrentGyr = "";
            }
        
            // handle screencolor metadata "...[screencolor:red|green|blue|white]..."
            if (fCurrentColor.size() > 0) {
                if ((fCurrentColor == "red") && (fRedReader == 0)) {
                    fRedReader = new ZoneReader(zone, min, max);
                    fHasScreenControl = true;
                } else if ((fCurrentColor == "green") && (fGreenReader == 0)) {
                    fGreenReader = new ZoneReader(zone, min, max);
                    fHasScreenControl = true;
                } else if ((fCurrentColor == "blue") && (fBlueReader == 0)) {
                    fBlueReader = new ZoneReader(zone, min, max);
                    fHasScreenControl = true;
                } else if ((fCurrentColor == "white") && (fRedReader == 0) && (fGreenReader == 0) && (fBlueReader == 0)) {
                    fRedReader = new ZoneReader(zone, min, max);
                    fGreenReader = new ZoneReader(zone, min, max);
                    fBlueReader = new ZoneReader(zone, min, max);
                    fHasScreenControl = true;
                } else {
                    std::cerr << "incorrect screencolor metadata : " << fCurrentColor << std::endl;
                }
            }
            fCurrentColor = "";
            
            fMetaData.push_back(fCurrentMetadata);
            fCurrentMetadata.clear();
        }

        int getZoneIndex(std::vector<ZoneControl*>* table, int p, int val)
        {
            FAUSTFLOAT* zone = fZone[p];
            for (size_t i = 0; i < table[val].size(); i++) {
                if (zone == table[val][i]->getZone()) return int(i);
            }
            return -1;
        }
    
        void setConverter(std::vector<ZoneControl*>* table, int p, int val, int curve, double amin, double amid, double amax)
        {
            int id1 = getZoneIndex(table, p, 0);
            int id2 = getZoneIndex(table, p, 1);
            int id3 = getZoneIndex(table, p, 2);
            
            // Deactivates everywhere..
            if (id1 != -1) table[0][id1]->setActive(false);
            if (id2 != -1) table[1][id2]->setActive(false);
            if (id3 != -1) table[2][id3]->setActive(false);
            
            if (val == -1) { // Means: no more mapping...
                // So stay all deactivated...
            } else {
                int id4 = getZoneIndex(table, p, val);
                if (id4 != -1) {
                    // Reactivate the one we edit...
                    table[val][id4]->setMappingValues(curve, amin, amid, amax, fMin[p], fInit[p], fMax[p]);
                    table[val][id4]->setActive(true);
                } else {
                    // Allocate a new CurveZoneControl which is 'active' by default
                    FAUSTFLOAT* zone = fZone[p];
                    table[val].push_back(new CurveZoneControl(zone, curve, amin, amid, amax, fMin[p], fInit[p], fMax[p]));
                }
            }
        }
    
        void getConverter(std::vector<ZoneControl*>* table, int p, int& val, int& curve, double& amin, double& amid, double& amax)
        {
            int id1 = getZoneIndex(table, p, 0);
            int id2 = getZoneIndex(table, p, 1);
            int id3 = getZoneIndex(table, p, 2);
            
            if (id1 != -1) {
                val = 0;
                curve = table[val][id1]->getCurve();
                table[val][id1]->getMappingValues(amin, amid, amax);
            } else if (id2 != -1) {
                val = 1;
                curve = table[val][id2]->getCurve();
                table[val][id2]->getMappingValues(amin, amid, amax);
            } else if (id3 != -1) {
                val = 2;
                curve = table[val][id3]->getCurve();
                table[val][id3]->getMappingValues(amin, amid, amax);
            } else {
                val = -1; // No mapping
                curve = 0;
                amin = -100.;
                amid = 0.;
                amax = 100.;
            }
        }

     public:
    
        enum Type { kAcc = 0, kGyr = 1, kNoType };
   
        APIUI() : fNumParameters(0), fHasScreenControl(false), fRedReader(0), fGreenReader(0), fBlueReader(0), fCurrentScale(kLin)
        {}

        virtual ~APIUI()
        {
            for (auto& it : fConversion) delete it;
            for (int i = 0; i < 3; i++) {
                for (auto& it : fAcc[i]) delete it;
                for (auto& it : fGyr[i]) delete it;
            }
            delete fRedReader;
            delete fGreenReader;
            delete fBlueReader;
        }
    
        // -- widget's layouts

        virtual void openTabBox(const char* label) { pushLabel(label); }
        virtual void openHorizontalBox(const char* label) { pushLabel(label); }
        virtual void openVerticalBox(const char* label) { pushLabel(label); }
        virtual void closeBox() { popLabel(); }

        // -- active widgets

        virtual void addButton(const char* label, FAUSTFLOAT* zone)
        {
            addParameter(label, zone, 0, 0, 1, 1, kButton);
        }

        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            addParameter(label, zone, 0, 0, 1, 1, kCheckButton);
        }

        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addParameter(label, zone, init, min, max, step, kVSlider);
        }

        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addParameter(label, zone, init, min, max, step, kHSlider);
        }

        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addParameter(label, zone, init, min, max, step, kNumEntry);
        }

        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            addParameter(label, zone, min, min, max, (max-min)/1000.0, kHBargraph);
        }

        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            addParameter(label, zone, min, min, max, (max-min)/1000.0, kVBargraph);
        }
    
        // -- soundfiles
    
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}

        // -- metadata declarations

        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {
            // Keep metadata
            fCurrentMetadata[key] = val;
            
            if (strcmp(key, "scale") == 0) {
                if (strcmp(val, "log") == 0) {
                    fCurrentScale = kLog;
                } else if (strcmp(val, "exp") == 0) {
                    fCurrentScale = kExp;
                } else {
                    fCurrentScale = kLin;
                }
            } else if (strcmp(key, "unit") == 0) {
                fCurrentUnit = val;
            } else if (strcmp(key, "acc") == 0) {
                fCurrentAcc = val;
            } else if (strcmp(key, "gyr") == 0) {
                fCurrentGyr = val;
            } else if (strcmp(key, "screencolor") == 0) {
                fCurrentColor = val; // val = "red", "green", "blue" or "white"
            } else if (strcmp(key, "tooltip") == 0) {
                fCurrentTooltip = val;
            }
        }

        virtual void declare(const char* key, const char* val)
        {}

		//-------------------------------------------------------------------------------
		// Simple API part
		//-------------------------------------------------------------------------------
		int getParamsCount() { return fNumParameters; }
        int getParamIndex(const char* path)
        {
            if (fPathMap.find(path) != fPathMap.end()) {
                return fPathMap[path];
            } else if (fLabelMap.find(path) != fLabelMap.end()) {
                return fLabelMap[path];
            } else {
                return -1;
            }
        }
        const char* getParamAddress(int p) { return fPaths[p].c_str(); }
        const char* getParamLabel(int p) { return fLabels[p].c_str(); }
        std::map<const char*, const char*> getMetadata(int p)
        {
            std::map<const char*, const char*> res;
            std::map<std::string, std::string> metadata = fMetaData[p];
            for (auto it : metadata) {
                res[it.first.c_str()] = it.second.c_str();
            }
            return res;
        }

        const char* getMetadata(int p, const char* key)
        {
            return (fMetaData[p].find(key) != fMetaData[p].end()) ? fMetaData[p][key].c_str() : "";
        }
        FAUSTFLOAT getParamMin(int p) { return fMin[p]; }
        FAUSTFLOAT getParamMax(int p) { return fMax[p]; }
        FAUSTFLOAT getParamStep(int p) { return fStep[p]; }
        FAUSTFLOAT getParamInit(int p) { return fInit[p]; }

        FAUSTFLOAT* getParamZone(int p) { return fZone[p]; }
    
        FAUSTFLOAT getParamValue(int p) { return *fZone[p]; }
        FAUSTFLOAT getParamValue(const char* path)
        {
            int index = getParamIndex(path);
            return (index >= 0) ? getParamValue(index) : FAUSTFLOAT(0);
        }
    
        void setParamValue(int p, FAUSTFLOAT v) { *fZone[p] = v; }
        void setParamValue(const char* path, FAUSTFLOAT v)
        {
            int index = getParamIndex(path);
            if (index >= 0) setParamValue(index, v);
        }

        double getParamRatio(int p) { return fConversion[p]->faust2ui(*fZone[p]); }
        void setParamRatio(int p, double r) { *fZone[p] = fConversion[p]->ui2faust(r); }

        double value2ratio(int p, double r)	{ return fConversion[p]->faust2ui(r); }
        double ratio2value(int p, double r)	{ return fConversion[p]->ui2faust(r); }
    
        /**
         * Return the control type (kAcc, kGyr, or -1) for a given parameter
         *
         * @param p - the UI parameter index
         *
         * @return the type
         */
        Type getParamType(int p)
        {
            if (p >= 0) {
                if (getZoneIndex(fAcc, p, 0) != -1
                    || getZoneIndex(fAcc, p, 1) != -1
                    || getZoneIndex(fAcc, p, 2) != -1) {
                    return kAcc;
                } else if (getZoneIndex(fGyr, p, 0) != -1
                           || getZoneIndex(fGyr, p, 1) != -1
                           || getZoneIndex(fGyr, p, 2) != -1) {
                    return kGyr;
                }
            }
            return kNoType;
        }
    
        /**
         * Return the Item type (kButton = 0, kCheckButton, kVSlider, kHSlider, kNumEntry, kHBargraph, kVBargraph) for a given parameter
         *
         * @param p - the UI parameter index
         *
         * @return the Item type
         */
        ItemType getParamItemType(int p)
        {
            return fItemType[p];
        }
   
        /**
         * Set a new value coming from an accelerometer, propagate it to all relevant FAUSTFLOAT* zones.
         *
         * @param acc - 0 for X accelerometer, 1 for Y accelerometer, 2 for Z accelerometer
         * @param value - the new value
         *
         */
        void propagateAcc(int acc, double value)
        {
            for (size_t i = 0; i < fAcc[acc].size(); i++) {
                fAcc[acc][i]->update(value);
            }
        }
    
        /**
         * Used to edit accelerometer curves and mapping. Set curve and related mapping for a given UI parameter.
         *
         * @param p - the UI parameter index
         * @param acc - 0 for X accelerometer, 1 for Y accelerometer, 2 for Z accelerometer (-1 means "no mapping")
         * @param curve - between 0 and 3
         * @param amin - mapping 'min' point
         * @param amid - mapping 'middle' point
         * @param amax - mapping 'max' point
         *
         */
        void setAccConverter(int p, int acc, int curve, double amin, double amid, double amax)
        {
            setConverter(fAcc, p, acc, curve, amin, amid, amax);
        }
    
        /**
         * Used to edit gyroscope curves and mapping. Set curve and related mapping for a given UI parameter.
         *
         * @param p - the UI parameter index
         * @param acc - 0 for X gyroscope, 1 for Y gyroscope, 2 for Z gyroscope (-1 means "no mapping")
         * @param curve - between 0 and 3
         * @param amin - mapping 'min' point
         * @param amid - mapping 'middle' point
         * @param amax - mapping 'max' point
         *
         */
        void setGyrConverter(int p, int gyr, int curve, double amin, double amid, double amax)
        {
             setConverter(fGyr, p, gyr, curve, amin, amid, amax);
        }
    
        /**
         * Used to edit accelerometer curves and mapping. Get curve and related mapping for a given UI parameter.
         *
         * @param p - the UI parameter index
         * @param acc - the acc value to be retrieved (-1 means "no mapping")
         * @param curve - the curve value to be retrieved
         * @param amin - the amin value to be retrieved
         * @param amid - the amid value to be retrieved
         * @param amax - the amax value to be retrieved
         *
         */
        void getAccConverter(int p, int& acc, int& curve, double& amin, double& amid, double& amax)
        {
            getConverter(fAcc, p, acc, curve, amin, amid, amax);
        }

        /**
         * Used to edit gyroscope curves and mapping. Get curve and related mapping for a given UI parameter.
         *
         * @param p - the UI parameter index
         * @param gyr - the gyr value to be retrieved (-1 means "no mapping")
         * @param curve - the curve value to be retrieved
         * @param amin - the amin value to be retrieved
         * @param amid - the amid value to be retrieved
         * @param amax - the amax value to be retrieved
         *
         */
        void getGyrConverter(int p, int& gyr, int& curve, double& amin, double& amid, double& amax)
        {
            getConverter(fGyr, p, gyr, curve, amin, amid, amax);
        }
    
        /**
         * Set a new value coming from an gyroscope, propagate it to all relevant FAUSTFLOAT* zones.
         *
         * @param gyr - 0 for X gyroscope, 1 for Y gyroscope, 2 for Z gyroscope
         * @param value - the new value
         *
         */
        void propagateGyr(int gyr, double value)
        {
            for (size_t i = 0; i < fGyr[gyr].size(); i++) {
                fGyr[gyr][i]->update(value);
            }
        }
    
        /**
         * Get the number of FAUSTFLOAT* zones controlled with the accelerometer
         *
         * @param acc - 0 for X accelerometer, 1 for Y accelerometer, 2 for Z accelerometer
         * @return the number of zones
         *
         */
        int getAccCount(int acc)
        {
            return (acc >= 0 && acc < 3) ? int(fAcc[acc].size()) : 0;
        }
    
        /**
         * Get the number of FAUSTFLOAT* zones controlled with the gyroscope
         *
         * @param gyr - 0 for X gyroscope, 1 for Y gyroscope, 2 for Z gyroscope
         * @param the number of zones
         *
         */
        int getGyrCount(int gyr)
        {
            return (gyr >= 0 && gyr < 3) ? int(fGyr[gyr].size()) : 0;
        }
   
        // getScreenColor() : -1 means no screen color control (no screencolor metadata found)
        // otherwise return 0x00RRGGBB a ready to use color
        int getScreenColor()
        {
            if (fHasScreenControl) {
                int r = (fRedReader) ? fRedReader->getValue() : 0;
                int g = (fGreenReader) ? fGreenReader->getValue() : 0;
                int b = (fBlueReader) ? fBlueReader->getValue() : 0;
                return (r<<16) | (g<<8) | b;
            } else {
                return -1;
            }
        }
 
};

#endif
/**************************  END  APIUI.h **************************/
/************************** BEGIN dsp.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __dsp__
#define __dsp__

#include <string>
#include <vector>

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

struct UI;
struct Meta;

/**
 * DSP memory manager.
 */

struct dsp_memory_manager {
    
    virtual ~dsp_memory_manager() {}
    
    virtual void* allocate(size_t size) = 0;
    virtual void destroy(void* ptr) = 0;
    
};

/**
* Signal processor definition.
*/

class dsp {

    public:

        dsp() {}
        virtual ~dsp() {}

        /* Return instance number of audio inputs */
        virtual int getNumInputs() = 0;
    
        /* Return instance number of audio outputs */
        virtual int getNumOutputs() = 0;
    
        /**
         * Trigger the ui_interface parameter with instance specific calls
         * to 'openTabBox', 'addButton', 'addVerticalSlider'... in order to build the UI.
         *
         * @param ui_interface - the user interface builder
         */
        virtual void buildUserInterface(UI* ui_interface) = 0;
    
        /* Returns the sample rate currently used by the instance */
        virtual int getSampleRate() = 0;
    
        /**
         * Global init, calls the following methods:
         * - static class 'classInit': static tables initialization
         * - 'instanceInit': constants and instance state initialization
         *
         * @param sample_rate - the sampling rate in Hertz
         */
        virtual void init(int sample_rate) = 0;

        /**
         * Init instance state
         *
         * @param sample_rate - the sampling rate in Hertz
         */
        virtual void instanceInit(int sample_rate) = 0;

        /**
         * Init instance constant state
         *
         * @param sample_rate - the sampling rate in Hertz
         */
        virtual void instanceConstants(int sample_rate) = 0;
    
        /* Init default control parameters values */
        virtual void instanceResetUserInterface() = 0;
    
        /* Init instance state (like delay lines...) but keep the control parameter values */
        virtual void instanceClear() = 0;
 
        /**
         * Return a clone of the instance.
         *
         * @return a copy of the instance on success, otherwise a null pointer.
         */
        virtual dsp* clone() = 0;
    
        /**
         * Trigger the Meta* parameter with instance specific calls to 'declare' (key, value) metadata.
         *
         * @param m - the Meta* meta user
         */
        virtual void metadata(Meta* m) = 0;
    
        /**
         * DSP instance computation, to be called with successive in/out audio buffers.
         *
         * @param count - the number of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
         *
         */
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) = 0;
    
        /**
         * DSP instance computation: alternative method to be used by subclasses.
         *
         * @param date_usec - the timestamp in microsec given by audio driver.
         * @param count - the number of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (either float, double or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (either float, double or quad)
         *
         */
        virtual void compute(double /*date_usec*/, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
       
};

/**
 * Generic DSP decorator.
 */

class decorator_dsp : public dsp {

    protected:

        dsp* fDSP;

    public:

        decorator_dsp(dsp* dsp = nullptr):fDSP(dsp) {}
        virtual ~decorator_dsp() { delete fDSP; }

        virtual int getNumInputs() { return fDSP->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP->getNumOutputs(); }
        virtual void buildUserInterface(UI* ui_interface) { fDSP->buildUserInterface(ui_interface); }
        virtual int getSampleRate() { return fDSP->getSampleRate(); }
        virtual void init(int sample_rate) { fDSP->init(sample_rate); }
        virtual void instanceInit(int sample_rate) { fDSP->instanceInit(sample_rate); }
        virtual void instanceConstants(int sample_rate) { fDSP->instanceConstants(sample_rate); }
        virtual void instanceResetUserInterface() { fDSP->instanceResetUserInterface(); }
        virtual void instanceClear() { fDSP->instanceClear(); }
        virtual decorator_dsp* clone() { return new decorator_dsp(fDSP->clone()); }
        virtual void metadata(Meta* m) { fDSP->metadata(m); }
        // Beware: subclasses usually have to overload the two 'compute' methods
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(count, inputs, outputs); }
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(date_usec, count, inputs, outputs); }
    
};

/**
 * DSP factory class.
 */

class dsp_factory {
    
    protected:
    
        // So that to force sub-classes to use deleteDSPFactory(dsp_factory* factory);
        virtual ~dsp_factory() {}
    
    public:
    
        virtual std::string getName() = 0;
        virtual std::string getSHAKey() = 0;
        virtual std::string getDSPCode() = 0;
        virtual std::string getCompileOptions() = 0;
        virtual std::vector<std::string> getLibraryList() = 0;
        virtual std::vector<std::string> getIncludePathnames() = 0;
    
        virtual dsp* createDSPInstance() = 0;
    
        virtual void setMemoryManager(dsp_memory_manager* manager) = 0;
        virtual dsp_memory_manager* getMemoryManager() = 0;
    
};

/**
 * On Intel set FZ (Flush to Zero) and DAZ (Denormals Are Zero)
 * flags to avoid costly denormals.
 */

#ifdef __SSE__
    #include <xmmintrin.h>
    #ifdef __SSE2__
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8040)
    #else
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8000)
    #endif
#else
    #define AVOIDDENORMALS
#endif

#endif
/**************************  END  dsp.h **************************/

// BEGIN-FAUSTDSP


#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

/* link with : "" */
#include <algorithm>
#include <cmath>
#include <math.h>

static float mydsp_faustpower2_f(float value) {
	return (value * value);
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class mydsp : public dsp {
	
 private:
	
	FAUSTFLOAT fHslider0;
	float fRec2_perm[4];
	FAUSTFLOAT fHslider1;
	float fRec3_perm[4];
	FAUSTFLOAT fHslider2;
	float fRec4_perm[4];
	FAUSTFLOAT fHslider3;
	float fRec10_perm[4];
	FAUSTFLOAT fHslider4;
	float fRec11_perm[4];
	float fYec0[65536];
	int fYec0_idx;
	int fYec0_idx_save;
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fRec8_perm[4];
	FAUSTFLOAT fHslider5;
	float fRec12_perm[4];
	FAUSTFLOAT fHslider6;
	float fRec13_perm[4];
	float fYec1[65536];
	int fYec1_idx;
	int fYec1_idx_save;
	float fRec9_perm[4];
	FAUSTFLOAT fHslider7;
	float fRec14_perm[4];
	float fRec7_perm[4];
	float fRec6_perm[4];
	float fRec5_perm[4];
	float fYec2[65536];
	int fYec2_idx;
	int fYec2_idx_save;
	float fRec18_perm[4];
	float fRec19_perm[4];
	float fRec17_perm[4];
	float fRec16_perm[4];
	float fRec15_perm[4];
	FAUSTFLOAT fHslider8;
	float fRec20_perm[4];
	FAUSTFLOAT fHslider9;
	float fRec21_perm[4];
	float fConst2;
	float fRec1_perm[4];
	float fRec0_perm[4];
	float fRec23_perm[4];
	float fRec22_perm[4];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("author", "Till Bovermann");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.1");
		m->declare("description", "bool_osc FB alternative 1");
		m->declare("filename", "BoolOscFB1.dsp");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/tf2:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2s:license", "MIT-style STK-4.3 license");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.3");
		m->declare("name", "BoolOscFB1");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "0.1");
		m->declare("reference", "http://rottingsounds.org");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
	}

	virtual int getNumInputs() {
		return 0;
	}
	virtual int getNumOutputs() {
		return 2;
	}
	virtual int getInputRate(int channel) {
		int rate;
		switch ((channel)) {
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	virtual int getOutputRate(int channel) {
		int rate;
		switch ((channel)) {
			case 0: {
				rate = 1;
				break;
			}
			case 1: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = (0.25f * fConst0);
		fConst2 = (3.14159274f / fConst0);
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.5f);
		fHslider1 = FAUSTFLOAT(1.0f);
		fHslider2 = FAUSTFLOAT(0.25f);
		fHslider3 = FAUSTFLOAT(0.0001f);
		fHslider4 = FAUSTFLOAT(0.0001f);
		fHslider5 = FAUSTFLOAT(0.0001f);
		fHslider6 = FAUSTFLOAT(0.0001f);
		fHslider7 = FAUSTFLOAT(0.01f);
		fHslider8 = FAUSTFLOAT(1.0f);
		fHslider9 = FAUSTFLOAT(10000.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 4); l0 = (l0 + 1)) {
			fRec2_perm[l0] = 0.0f;
		}
		for (int l1 = 0; (l1 < 4); l1 = (l1 + 1)) {
			fRec3_perm[l1] = 0.0f;
		}
		for (int l2 = 0; (l2 < 4); l2 = (l2 + 1)) {
			fRec4_perm[l2] = 0.0f;
		}
		for (int l3 = 0; (l3 < 4); l3 = (l3 + 1)) {
			fRec10_perm[l3] = 0.0f;
		}
		for (int l4 = 0; (l4 < 4); l4 = (l4 + 1)) {
			fRec11_perm[l4] = 0.0f;
		}
		for (int l5 = 0; (l5 < 65536); l5 = (l5 + 1)) {
			fYec0[l5] = 0.0f;
		}
		fYec0_idx = 0;
		fYec0_idx_save = 0;
		for (int l6 = 0; (l6 < 4); l6 = (l6 + 1)) {
			fRec8_perm[l6] = 0.0f;
		}
		for (int l7 = 0; (l7 < 4); l7 = (l7 + 1)) {
			fRec12_perm[l7] = 0.0f;
		}
		for (int l8 = 0; (l8 < 4); l8 = (l8 + 1)) {
			fRec13_perm[l8] = 0.0f;
		}
		for (int l9 = 0; (l9 < 65536); l9 = (l9 + 1)) {
			fYec1[l9] = 0.0f;
		}
		fYec1_idx = 0;
		fYec1_idx_save = 0;
		for (int l10 = 0; (l10 < 4); l10 = (l10 + 1)) {
			fRec9_perm[l10] = 0.0f;
		}
		for (int l11 = 0; (l11 < 4); l11 = (l11 + 1)) {
			fRec14_perm[l11] = 0.0f;
		}
		for (int l12 = 0; (l12 < 4); l12 = (l12 + 1)) {
			fRec7_perm[l12] = 0.0f;
		}
		for (int l13 = 0; (l13 < 4); l13 = (l13 + 1)) {
			fRec6_perm[l13] = 0.0f;
		}
		for (int l14 = 0; (l14 < 4); l14 = (l14 + 1)) {
			fRec5_perm[l14] = 0.0f;
		}
		for (int l15 = 0; (l15 < 65536); l15 = (l15 + 1)) {
			fYec2[l15] = 0.0f;
		}
		fYec2_idx = 0;
		fYec2_idx_save = 0;
		for (int l16 = 0; (l16 < 4); l16 = (l16 + 1)) {
			fRec18_perm[l16] = 0.0f;
		}
		for (int l17 = 0; (l17 < 4); l17 = (l17 + 1)) {
			fRec19_perm[l17] = 0.0f;
		}
		for (int l18 = 0; (l18 < 4); l18 = (l18 + 1)) {
			fRec17_perm[l18] = 0.0f;
		}
		for (int l19 = 0; (l19 < 4); l19 = (l19 + 1)) {
			fRec16_perm[l19] = 0.0f;
		}
		for (int l20 = 0; (l20 < 4); l20 = (l20 + 1)) {
			fRec15_perm[l20] = 0.0f;
		}
		for (int l21 = 0; (l21 < 4); l21 = (l21 + 1)) {
			fRec20_perm[l21] = 0.0f;
		}
		for (int l22 = 0; (l22 < 4); l22 = (l22 + 1)) {
			fRec21_perm[l22] = 0.0f;
		}
		for (int l23 = 0; (l23 < 4); l23 = (l23 + 1)) {
			fRec1_perm[l23] = 0.0f;
		}
		for (int l24 = 0; (l24 < 4); l24 = (l24 + 1)) {
			fRec0_perm[l24] = 0.0f;
		}
		for (int l25 = 0; (l25 < 4); l25 = (l25 + 1)) {
			fRec23_perm[l25] = 0.0f;
		}
		for (int l26 = 0; (l26 < 4); l26 = (l26 + 1)) {
			fRec22_perm[l26] = 0.0f;
		}
	}
	
	virtual void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	virtual void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual mydsp* clone() {
		return new mydsp();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("BoolOscFB1");
		ui_interface->declare(&fHslider4, "01", "");
		ui_interface->declare(&fHslider4, "scale", "exp");
		ui_interface->addHorizontalSlider("mod1", &fHslider4, 9.99999975e-05f, 9.99999975e-05f, 1.0f, 9.99999975e-06f);
		ui_interface->declare(&fHslider6, "02", "");
		ui_interface->declare(&fHslider6, "scale", "exp");
		ui_interface->addHorizontalSlider("mod2", &fHslider6, 9.99999975e-05f, 9.99999975e-05f, 1.0f, 9.99999975e-06f);
		ui_interface->declare(&fHslider5, "03", "");
		ui_interface->declare(&fHslider5, "scale", "exp");
		ui_interface->addHorizontalSlider("bias1", &fHslider5, 9.99999975e-05f, 9.99999975e-05f, 1.0f, 9.99999975e-06f);
		ui_interface->declare(&fHslider3, "04", "");
		ui_interface->declare(&fHslider3, "scale", "exp");
		ui_interface->addHorizontalSlider("bias2", &fHslider3, 9.99999975e-05f, 9.99999975e-05f, 1.0f, 9.99999975e-06f);
		ui_interface->declare(&fHslider7, "05", "");
		ui_interface->addHorizontalSlider("leak", &fHslider7, 0.00999999978f, 0.0f, 1.0f, 9.99999975e-05f);
		ui_interface->declare(&fHslider1, "06", "");
		ui_interface->declare(&fHslider1, "scale", "exp");
		ui_interface->addHorizontalSlider("distort", &fHslider1, 1.0f, 1.0f, 10.0f, 0.00100000005f);
		ui_interface->declare(&fHslider0, "07", "");
		ui_interface->addHorizontalSlider("amp", &fHslider0, 0.5f, 0.0f, 1.0f, 0.00100000005f);
		ui_interface->declare(&fHslider8, "08", "");
		ui_interface->addHorizontalSlider("width", &fHslider8, 1.0f, 0.0f, 1.0f, 0.00100000005f);
		ui_interface->declare(&fHslider2, "09", "");
		ui_interface->addHorizontalSlider("rot", &fHslider2, 0.25f, 0.0f, 1.0f, 0.00100000005f);
		ui_interface->declare(&fHslider9, "10", "");
		ui_interface->declare(&fHslider9, "scale", "exp");
		ui_interface->addHorizontalSlider("lpfreq", &fHslider9, 10000.0f, 10.0f, 20000.0f, 1.0f);
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0_ptr = outputs[0];
		FAUSTFLOAT* output1_ptr = outputs[1];
		float fSlow0 = (0.00100000005f * float(fHslider0));
		float fRec2_tmp[36];
		float* fRec2 = &fRec2_tmp[4];
		float fSlow1 = (0.00100000005f * float(fHslider1));
		float fRec3_tmp[36];
		float* fRec3 = &fRec3_tmp[4];
		float fSlow2 = (0.00100000005f * float(fHslider2));
		float fRec4_tmp[36];
		float* fRec4 = &fRec4_tmp[4];
		float fSlow3 = (0.00100000005f * float(fHslider3));
		float fRec10_tmp[36];
		float* fRec10 = &fRec10_tmp[4];
		float fSlow4 = (0.00100000005f * float(fHslider4));
		float fRec11_tmp[36];
		float* fRec11 = &fRec11_tmp[4];
		int iZec0[32];
		int iZec1[32];
		float fRec8_tmp[36];
		float* fRec8 = &fRec8_tmp[4];
		float fSlow5 = (0.00100000005f * float(fHslider5));
		float fRec12_tmp[36];
		float* fRec12 = &fRec12_tmp[4];
		float fSlow6 = (0.00100000005f * float(fHslider6));
		float fRec13_tmp[36];
		float* fRec13 = &fRec13_tmp[4];
		float fRec9_tmp[36];
		float* fRec9 = &fRec9_tmp[4];
		float fSlow7 = (0.00100000005f * float(fHslider7));
		float fRec14_tmp[36];
		float* fRec14 = &fRec14_tmp[4];
		float fZec2[32];
		float fRec7_tmp[36];
		float* fRec7 = &fRec7_tmp[4];
		float fRec6_tmp[36];
		float* fRec6 = &fRec6_tmp[4];
		float fRec5_tmp[36];
		float* fRec5 = &fRec5_tmp[4];
		float fRec18_tmp[36];
		float* fRec18 = &fRec18_tmp[4];
		float fRec19_tmp[36];
		float* fRec19 = &fRec19_tmp[4];
		float fRec17_tmp[36];
		float* fRec17 = &fRec17_tmp[4];
		float fRec16_tmp[36];
		float* fRec16 = &fRec16_tmp[4];
		float fRec15_tmp[36];
		float* fRec15 = &fRec15_tmp[4];
		float fSlow8 = (0.00100000005f * float(fHslider8));
		float fRec20_tmp[36];
		float* fRec20 = &fRec20_tmp[4];
		float fSlow9 = (0.00100000005f * float(fHslider9));
		float fRec21_tmp[36];
		float* fRec21 = &fRec21_tmp[4];
		float fZec3[32];
		float fZec4[32];
		float fZec5[32];
		float fZec6[32];
		float fZec7[32];
		float fZec8[32];
		float fZec9[32];
		float fZec10[32];
		float fZec11[32];
		float fZec12[32];
		float fZec13[32];
		float fRec1_tmp[36];
		float* fRec1 = &fRec1_tmp[4];
		float fZec14[32];
		float fZec15[32];
		float fRec0_tmp[36];
		float* fRec0 = &fRec0_tmp[4];
		float fRec23_tmp[36];
		float* fRec23 = &fRec23_tmp[4];
		float fRec22_tmp[36];
		float* fRec22 = &fRec22_tmp[4];
		int vindex = 0;
		/* Main loop */
		for (vindex = 0; (vindex <= (count - 32)); vindex = (vindex + 32)) {
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			FAUSTFLOAT* output1 = &output1_ptr[vindex];
			int vsize = 32;
			/* Recursive loop 0 */
			/* Pre code */
			for (int j18 = 0; (j18 < 4); j18 = (j18 + 1)) {
				fRec14_tmp[j18] = fRec14_perm[j18];
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec14[i] = (fSlow7 + (0.999000013f * fRec14[(i - 1)]));
			}
			/* Post code */
			for (int j19 = 0; (j19 < 4); j19 = (j19 + 1)) {
				fRec14_perm[j19] = fRec14_tmp[(vsize + j19)];
			}
			/* Recursive loop 1 */
			/* Pre code */
			for (int j6 = 0; (j6 < 4); j6 = (j6 + 1)) {
				fRec10_tmp[j6] = fRec10_perm[j6];
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec10[i] = (fSlow3 + (0.999000013f * fRec10[(i - 1)]));
			}
			/* Post code */
			for (int j7 = 0; (j7 < 4); j7 = (j7 + 1)) {
				fRec10_perm[j7] = fRec10_tmp[(vsize + j7)];
			}
			/* Recursive loop 2 */
			/* Pre code */
			for (int j8 = 0; (j8 < 4); j8 = (j8 + 1)) {
				fRec11_tmp[j8] = fRec11_perm[j8];
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec11[i] = (fSlow4 + (0.999000013f * fRec11[(i - 1)]));
			}
			/* Post code */
			for (int j9 = 0; (j9 < 4); j9 = (j9 + 1)) {
				fRec11_perm[j9] = fRec11_tmp[(vsize + j9)];
			}
			/* Recursive loop 3 */
			/* Pre code */
			for (int j12 = 0; (j12 < 4); j12 = (j12 + 1)) {
				fRec12_tmp[j12] = fRec12_perm[j12];
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec12[i] = (fSlow5 + (0.999000013f * fRec12[(i - 1)]));
			}
			/* Post code */
			for (int j13 = 0; (j13 < 4); j13 = (j13 + 1)) {
				fRec12_perm[j13] = fRec12_tmp[(vsize + j13)];
			}
			/* Recursive loop 4 */
			/* Pre code */
			for (int j14 = 0; (j14 < 4); j14 = (j14 + 1)) {
				fRec13_tmp[j14] = fRec13_perm[j14];
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec13[i] = (fSlow6 + (0.999000013f * fRec13[(i - 1)]));
			}
			/* Post code */
			for (int j15 = 0; (j15 < 4); j15 = (j15 + 1)) {
				fRec13_perm[j15] = fRec13_tmp[(vsize + j15)];
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec2[i] = (1.0f - (0.00100000005f * fRec14[i]));
			}
			/* Recursive loop 6 */
			/* Pre code */
			for (int j4 = 0; (j4 < 4); j4 = (j4 + 1)) {
				fRec4_tmp[j4] = fRec4_perm[j4];
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec4[i] = (fSlow2 + (0.999000013f * fRec4[(i - 1)]));
			}
			/* Post code */
			for (int j5 = 0; (j5 < 4); j5 = (j5 + 1)) {
				fRec4_perm[j5] = fRec4_tmp[(vsize + j5)];
			}
			/* Recursive loop 7 */
			/* Pre code */
			fYec0_idx = ((fYec0_idx + fYec0_idx_save) & 65535);
			for (int j10 = 0; (j10 < 4); j10 = (j10 + 1)) {
				fRec8_tmp[j10] = fRec8_perm[j10];
			}
			fYec1_idx = ((fYec1_idx + fYec1_idx_save) & 65535);
			for (int j16 = 0; (j16 < 4); j16 = (j16 + 1)) {
				fRec9_tmp[j16] = fRec9_perm[j16];
			}
			for (int j20 = 0; (j20 < 4); j20 = (j20 + 1)) {
				fRec7_tmp[j20] = fRec7_perm[j20];
			}
			for (int j22 = 0; (j22 < 4); j22 = (j22 + 1)) {
				fRec6_tmp[j22] = fRec6_perm[j22];
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec0[i] = int(fRec8[(i - 1)]);
				iZec1[i] = int(fRec9[(i - 1)]);
				fYec0[((i + fYec0_idx) & 65535)] = std::rint((1.0f - float(((iZec0[i] ^ iZec1[i]) ^ iZec0[i]))));
				fRec8[i] = fYec0[(((i + fYec0_idx) - int(std::min<float>(fConst1, std::max<float>(0.0f, std::fmod(std::max<float>(0.0f, (15000.0f * (fRec10[i] + (fRec11[i] * fRec6[(i - 1)])))), fConst1))))) & 65535)];
				fYec1[((i + fYec1_idx) & 65535)] = std::rint((1.0f - float(((iZec1[i] ^ iZec0[i]) & iZec1[i]))));
				fRec9[i] = fYec1[(((i + fYec1_idx) - int(std::min<float>(fConst1, std::max<float>(0.0f, std::fmod(std::max<float>(0.0f, (15000.0f * (fRec12[i] + (fRec13[i] * fRec6[(i - 1)])))), fConst1))))) & 65535)];
				fRec7[i] = ((fRec9[i] + (fZec2[i] * fRec7[(i - 1)])) - fRec9[(i - 1)]);
				fRec6[i] = fRec7[i];
			}
			/* Post code */
			fYec1_idx_save = vsize;
			fYec0_idx_save = vsize;
			for (int j11 = 0; (j11 < 4); j11 = (j11 + 1)) {
				fRec8_perm[j11] = fRec8_tmp[(vsize + j11)];
			}
			for (int j17 = 0; (j17 < 4); j17 = (j17 + 1)) {
				fRec9_perm[j17] = fRec9_tmp[(vsize + j17)];
			}
			for (int j21 = 0; (j21 < 4); j21 = (j21 + 1)) {
				fRec7_perm[j21] = fRec7_tmp[(vsize + j21)];
			}
			for (int j23 = 0; (j23 < 4); j23 = (j23 + 1)) {
				fRec6_perm[j23] = fRec6_tmp[(vsize + j23)];
			}
			/* Recursive loop 8 */
			/* Pre code */
			fYec2_idx = ((fYec2_idx + fYec2_idx_save) & 65535);
			for (int j26 = 0; (j26 < 4); j26 = (j26 + 1)) {
				fRec18_tmp[j26] = fRec18_perm[j26];
			}
			for (int j28 = 0; (j28 < 4); j28 = (j28 + 1)) {
				fRec19_tmp[j28] = fRec19_perm[j28];
			}
			for (int j30 = 0; (j30 < 4); j30 = (j30 + 1)) {
				fRec17_tmp[j30] = fRec17_perm[j30];
			}
			for (int j32 = 0; (j32 < 4); j32 = (j32 + 1)) {
				fRec16_tmp[j32] = fRec16_perm[j32];
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fYec2[((i + fYec2_idx) & 65535)] = std::rint((1.0f - float((int(fRec19[(i - 1)]) & int(fRec18[(i - 1)])))));
				fRec18[i] = fYec2[(((i + fYec2_idx) - int(std::min<float>(fConst1, std::max<float>(0.0f, std::fmod(std::max<float>(0.0f, (15000.0f * (fRec10[i] + (fRec13[i] * fRec16[(i - 1)])))), fConst1))))) & 65535)];
				fRec19[i] = fYec2[(((i + fYec2_idx) - int(std::min<float>(fConst1, std::max<float>(0.0f, std::fmod(std::max<float>(0.0f, (15000.0f * (fRec12[i] + (fRec11[i] * fRec16[(i - 1)])))), fConst1))))) & 65535)];
				fRec17[i] = ((fRec19[i] + (fZec2[i] * fRec17[(i - 1)])) - fRec19[(i - 1)]);
				fRec16[i] = fRec17[i];
			}
			/* Post code */
			fYec2_idx_save = vsize;
			for (int j27 = 0; (j27 < 4); j27 = (j27 + 1)) {
				fRec18_perm[j27] = fRec18_tmp[(vsize + j27)];
			}
			for (int j29 = 0; (j29 < 4); j29 = (j29 + 1)) {
				fRec19_perm[j29] = fRec19_tmp[(vsize + j29)];
			}
			for (int j31 = 0; (j31 < 4); j31 = (j31 + 1)) {
				fRec17_perm[j31] = fRec17_tmp[(vsize + j31)];
			}
			for (int j33 = 0; (j33 < 4); j33 = (j33 + 1)) {
				fRec16_perm[j33] = fRec16_tmp[(vsize + j33)];
			}
			/* Recursive loop 9 */
			/* Pre code */
			for (int j38 = 0; (j38 < 4); j38 = (j38 + 1)) {
				fRec21_tmp[j38] = fRec21_perm[j38];
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec21[i] = (fSlow9 + (0.999000013f * fRec21[(i - 1)]));
			}
			/* Post code */
			for (int j39 = 0; (j39 < 4); j39 = (j39 + 1)) {
				fRec21_perm[j39] = fRec21_tmp[(vsize + j39)];
			}
			/* Recursive loop 10 */
			/* Pre code */
			for (int j24 = 0; (j24 < 4); j24 = (j24 + 1)) {
				fRec5_tmp[j24] = fRec5_perm[j24];
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec5[i] = ((fRec6[i] + (0.999000013f * fRec5[(i - 1)])) - fRec6[(i - 1)]);
			}
			/* Post code */
			for (int j25 = 0; (j25 < 4); j25 = (j25 + 1)) {
				fRec5_perm[j25] = fRec5_tmp[(vsize + j25)];
			}
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec9[i] = std::tan((fConst2 * fRec21[i]));
			}
			/* Recursive loop 12 */
			/* Pre code */
			for (int j34 = 0; (j34 < 4); j34 = (j34 + 1)) {
				fRec15_tmp[j34] = fRec15_perm[j34];
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec15[i] = ((fRec16[i] + (0.999000013f * fRec15[(i - 1)])) - fRec16[(i - 1)]);
			}
			/* Post code */
			for (int j35 = 0; (j35 < 4); j35 = (j35 + 1)) {
				fRec15_perm[j35] = fRec15_tmp[(vsize + j35)];
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec3[i] = (3.14159274f * fRec4[i]);
			}
			/* Vectorizable loop 14 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec10[i] = (1.0f / fZec9[i]);
			}
			/* Recursive loop 15 */
			/* Pre code */
			for (int j36 = 0; (j36 < 4); j36 = (j36 + 1)) {
				fRec20_tmp[j36] = fRec20_perm[j36];
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec20[i] = (fSlow8 + (0.999000013f * fRec20[(i - 1)]));
			}
			/* Post code */
			for (int j37 = 0; (j37 < 4); j37 = (j37 + 1)) {
				fRec20_perm[j37] = fRec20_tmp[(vsize + j37)];
			}
			/* Vectorizable loop 16 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec4[i] = std::cos(fZec3[i]);
			}
			/* Vectorizable loop 17 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec5[i] = (fRec5[i] + fRec15[i]);
			}
			/* Vectorizable loop 18 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec6[i] = std::sin(fZec3[i]);
			}
			/* Recursive loop 19 */
			/* Pre code */
			for (int j2 = 0; (j2 < 4); j2 = (j2 + 1)) {
				fRec3_tmp[j2] = fRec3_perm[j2];
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec3[i] = (fSlow1 + (0.999000013f * fRec3[(i - 1)]));
			}
			/* Post code */
			for (int j3 = 0; (j3 < 4); j3 = (j3 + 1)) {
				fRec3_perm[j3] = fRec3_tmp[(vsize + j3)];
			}
			/* Vectorizable loop 20 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec8[i] = (fRec20[i] * ((fZec4[i] * (fRec5[i] - fRec15[i])) + (fZec6[i] * fZec5[i])));
			}
			/* Vectorizable loop 21 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec11[i] = (((fZec10[i] + -1.84775901f) / fZec9[i]) + 1.0f);
			}
			/* Vectorizable loop 22 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec12[i] = (1.0f - (1.0f / mydsp_faustpower2_f(fZec9[i])));
			}
			/* Vectorizable loop 23 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec13[i] = (((fZec10[i] + 1.84775901f) / fZec9[i]) + 1.0f);
			}
			/* Recursive loop 24 */
			/* Pre code */
			for (int j0 = 0; (j0 < 4); j0 = (j0 + 1)) {
				fRec2_tmp[j0] = fRec2_perm[j0];
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec2[i] = (fSlow0 + (0.999000013f * fRec2[(i - 1)]));
			}
			/* Post code */
			for (int j1 = 0; (j1 < 4); j1 = (j1 + 1)) {
				fRec2_perm[j1] = fRec2_tmp[(vsize + j1)];
			}
			/* Vectorizable loop 25 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec7[i] = ((fZec4[i] * fZec5[i]) + (fZec6[i] * (fRec15[i] - fRec5[i])));
			}
			/* Vectorizable loop 26 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec14[i] = (((fZec10[i] + -0.765366852f) / fZec9[i]) + 1.0f);
			}
			/* Vectorizable loop 27 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec15[i] = (((fZec10[i] + 0.765366852f) / fZec9[i]) + 1.0f);
			}
			/* Recursive loop 28 */
			/* Pre code */
			for (int j44 = 0; (j44 < 4); j44 = (j44 + 1)) {
				fRec23_tmp[j44] = fRec23_perm[j44];
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec23[i] = ((fRec2[i] * float(tanhf(float((0.25f * (fRec3[i] * (fZec7[i] - fZec8[i]))))))) - (((fZec11[i] * fRec23[(i - 2)]) + (2.0f * (fZec12[i] * fRec23[(i - 1)]))) / fZec13[i]));
			}
			/* Post code */
			for (int j45 = 0; (j45 < 4); j45 = (j45 + 1)) {
				fRec23_perm[j45] = fRec23_tmp[(vsize + j45)];
			}
			/* Recursive loop 29 */
			/* Pre code */
			for (int j40 = 0; (j40 < 4); j40 = (j40 + 1)) {
				fRec1_tmp[j40] = fRec1_perm[j40];
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec1[i] = ((fRec2[i] * float(tanhf(float((0.25f * (fRec3[i] * (fZec7[i] + fZec8[i]))))))) - (((fRec1[(i - 2)] * fZec11[i]) + (2.0f * (fRec1[(i - 1)] * fZec12[i]))) / fZec13[i]));
			}
			/* Post code */
			for (int j41 = 0; (j41 < 4); j41 = (j41 + 1)) {
				fRec1_perm[j41] = fRec1_tmp[(vsize + j41)];
			}
			/* Recursive loop 30 */
			/* Pre code */
			for (int j46 = 0; (j46 < 4); j46 = (j46 + 1)) {
				fRec22_tmp[j46] = fRec22_perm[j46];
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec22[i] = (((fRec23[(i - 2)] + (fRec23[i] + (2.0f * fRec23[(i - 1)]))) / fZec13[i]) - (((fZec14[i] * fRec22[(i - 2)]) + (2.0f * (fZec12[i] * fRec22[(i - 1)]))) / fZec15[i]));
			}
			/* Post code */
			for (int j47 = 0; (j47 < 4); j47 = (j47 + 1)) {
				fRec22_perm[j47] = fRec22_tmp[(vsize + j47)];
			}
			/* Recursive loop 31 */
			/* Pre code */
			for (int j42 = 0; (j42 < 4); j42 = (j42 + 1)) {
				fRec0_tmp[j42] = fRec0_perm[j42];
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec0[i] = (((fRec1[(i - 2)] + (fRec1[i] + (2.0f * fRec1[(i - 1)]))) / fZec13[i]) - (((fRec0[(i - 2)] * fZec14[i]) + (2.0f * (fZec12[i] * fRec0[(i - 1)]))) / fZec15[i]));
			}
			/* Post code */
			for (int j43 = 0; (j43 < 4); j43 = (j43 + 1)) {
				fRec0_perm[j43] = fRec0_tmp[(vsize + j43)];
			}
			/* Vectorizable loop 32 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				output1[i] = FAUSTFLOAT(((fRec22[(i - 2)] + (fRec22[i] + (2.0f * fRec22[(i - 1)]))) / fZec15[i]));
			}
			/* Vectorizable loop 33 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				output0[i] = FAUSTFLOAT(((fRec0[(i - 2)] + (fRec0[i] + (2.0f * fRec0[(i - 1)]))) / fZec15[i]));
			}
		}
		/* Remaining frames */
		if (vindex < count) {
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			FAUSTFLOAT* output1 = &output1_ptr[vindex];
			int vsize = (count - vindex);
			/* Recursive loop 0 */
			/* Pre code */
			for (int j18 = 0; (j18 < 4); j18 = (j18 + 1)) {
				fRec14_tmp[j18] = fRec14_perm[j18];
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec14[i] = (fSlow7 + (0.999000013f * fRec14[(i - 1)]));
			}
			/* Post code */
			for (int j19 = 0; (j19 < 4); j19 = (j19 + 1)) {
				fRec14_perm[j19] = fRec14_tmp[(vsize + j19)];
			}
			/* Recursive loop 1 */
			/* Pre code */
			for (int j6 = 0; (j6 < 4); j6 = (j6 + 1)) {
				fRec10_tmp[j6] = fRec10_perm[j6];
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec10[i] = (fSlow3 + (0.999000013f * fRec10[(i - 1)]));
			}
			/* Post code */
			for (int j7 = 0; (j7 < 4); j7 = (j7 + 1)) {
				fRec10_perm[j7] = fRec10_tmp[(vsize + j7)];
			}
			/* Recursive loop 2 */
			/* Pre code */
			for (int j8 = 0; (j8 < 4); j8 = (j8 + 1)) {
				fRec11_tmp[j8] = fRec11_perm[j8];
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec11[i] = (fSlow4 + (0.999000013f * fRec11[(i - 1)]));
			}
			/* Post code */
			for (int j9 = 0; (j9 < 4); j9 = (j9 + 1)) {
				fRec11_perm[j9] = fRec11_tmp[(vsize + j9)];
			}
			/* Recursive loop 3 */
			/* Pre code */
			for (int j12 = 0; (j12 < 4); j12 = (j12 + 1)) {
				fRec12_tmp[j12] = fRec12_perm[j12];
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec12[i] = (fSlow5 + (0.999000013f * fRec12[(i - 1)]));
			}
			/* Post code */
			for (int j13 = 0; (j13 < 4); j13 = (j13 + 1)) {
				fRec12_perm[j13] = fRec12_tmp[(vsize + j13)];
			}
			/* Recursive loop 4 */
			/* Pre code */
			for (int j14 = 0; (j14 < 4); j14 = (j14 + 1)) {
				fRec13_tmp[j14] = fRec13_perm[j14];
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec13[i] = (fSlow6 + (0.999000013f * fRec13[(i - 1)]));
			}
			/* Post code */
			for (int j15 = 0; (j15 < 4); j15 = (j15 + 1)) {
				fRec13_perm[j15] = fRec13_tmp[(vsize + j15)];
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec2[i] = (1.0f - (0.00100000005f * fRec14[i]));
			}
			/* Recursive loop 6 */
			/* Pre code */
			for (int j4 = 0; (j4 < 4); j4 = (j4 + 1)) {
				fRec4_tmp[j4] = fRec4_perm[j4];
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec4[i] = (fSlow2 + (0.999000013f * fRec4[(i - 1)]));
			}
			/* Post code */
			for (int j5 = 0; (j5 < 4); j5 = (j5 + 1)) {
				fRec4_perm[j5] = fRec4_tmp[(vsize + j5)];
			}
			/* Recursive loop 7 */
			/* Pre code */
			fYec0_idx = ((fYec0_idx + fYec0_idx_save) & 65535);
			for (int j10 = 0; (j10 < 4); j10 = (j10 + 1)) {
				fRec8_tmp[j10] = fRec8_perm[j10];
			}
			fYec1_idx = ((fYec1_idx + fYec1_idx_save) & 65535);
			for (int j16 = 0; (j16 < 4); j16 = (j16 + 1)) {
				fRec9_tmp[j16] = fRec9_perm[j16];
			}
			for (int j20 = 0; (j20 < 4); j20 = (j20 + 1)) {
				fRec7_tmp[j20] = fRec7_perm[j20];
			}
			for (int j22 = 0; (j22 < 4); j22 = (j22 + 1)) {
				fRec6_tmp[j22] = fRec6_perm[j22];
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec0[i] = int(fRec8[(i - 1)]);
				iZec1[i] = int(fRec9[(i - 1)]);
				fYec0[((i + fYec0_idx) & 65535)] = std::rint((1.0f - float(((iZec0[i] ^ iZec1[i]) ^ iZec0[i]))));
				fRec8[i] = fYec0[(((i + fYec0_idx) - int(std::min<float>(fConst1, std::max<float>(0.0f, std::fmod(std::max<float>(0.0f, (15000.0f * (fRec10[i] + (fRec11[i] * fRec6[(i - 1)])))), fConst1))))) & 65535)];
				fYec1[((i + fYec1_idx) & 65535)] = std::rint((1.0f - float(((iZec1[i] ^ iZec0[i]) & iZec1[i]))));
				fRec9[i] = fYec1[(((i + fYec1_idx) - int(std::min<float>(fConst1, std::max<float>(0.0f, std::fmod(std::max<float>(0.0f, (15000.0f * (fRec12[i] + (fRec13[i] * fRec6[(i - 1)])))), fConst1))))) & 65535)];
				fRec7[i] = ((fRec9[i] + (fZec2[i] * fRec7[(i - 1)])) - fRec9[(i - 1)]);
				fRec6[i] = fRec7[i];
			}
			/* Post code */
			fYec1_idx_save = vsize;
			fYec0_idx_save = vsize;
			for (int j11 = 0; (j11 < 4); j11 = (j11 + 1)) {
				fRec8_perm[j11] = fRec8_tmp[(vsize + j11)];
			}
			for (int j17 = 0; (j17 < 4); j17 = (j17 + 1)) {
				fRec9_perm[j17] = fRec9_tmp[(vsize + j17)];
			}
			for (int j21 = 0; (j21 < 4); j21 = (j21 + 1)) {
				fRec7_perm[j21] = fRec7_tmp[(vsize + j21)];
			}
			for (int j23 = 0; (j23 < 4); j23 = (j23 + 1)) {
				fRec6_perm[j23] = fRec6_tmp[(vsize + j23)];
			}
			/* Recursive loop 8 */
			/* Pre code */
			fYec2_idx = ((fYec2_idx + fYec2_idx_save) & 65535);
			for (int j26 = 0; (j26 < 4); j26 = (j26 + 1)) {
				fRec18_tmp[j26] = fRec18_perm[j26];
			}
			for (int j28 = 0; (j28 < 4); j28 = (j28 + 1)) {
				fRec19_tmp[j28] = fRec19_perm[j28];
			}
			for (int j30 = 0; (j30 < 4); j30 = (j30 + 1)) {
				fRec17_tmp[j30] = fRec17_perm[j30];
			}
			for (int j32 = 0; (j32 < 4); j32 = (j32 + 1)) {
				fRec16_tmp[j32] = fRec16_perm[j32];
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fYec2[((i + fYec2_idx) & 65535)] = std::rint((1.0f - float((int(fRec19[(i - 1)]) & int(fRec18[(i - 1)])))));
				fRec18[i] = fYec2[(((i + fYec2_idx) - int(std::min<float>(fConst1, std::max<float>(0.0f, std::fmod(std::max<float>(0.0f, (15000.0f * (fRec10[i] + (fRec13[i] * fRec16[(i - 1)])))), fConst1))))) & 65535)];
				fRec19[i] = fYec2[(((i + fYec2_idx) - int(std::min<float>(fConst1, std::max<float>(0.0f, std::fmod(std::max<float>(0.0f, (15000.0f * (fRec12[i] + (fRec11[i] * fRec16[(i - 1)])))), fConst1))))) & 65535)];
				fRec17[i] = ((fRec19[i] + (fZec2[i] * fRec17[(i - 1)])) - fRec19[(i - 1)]);
				fRec16[i] = fRec17[i];
			}
			/* Post code */
			fYec2_idx_save = vsize;
			for (int j27 = 0; (j27 < 4); j27 = (j27 + 1)) {
				fRec18_perm[j27] = fRec18_tmp[(vsize + j27)];
			}
			for (int j29 = 0; (j29 < 4); j29 = (j29 + 1)) {
				fRec19_perm[j29] = fRec19_tmp[(vsize + j29)];
			}
			for (int j31 = 0; (j31 < 4); j31 = (j31 + 1)) {
				fRec17_perm[j31] = fRec17_tmp[(vsize + j31)];
			}
			for (int j33 = 0; (j33 < 4); j33 = (j33 + 1)) {
				fRec16_perm[j33] = fRec16_tmp[(vsize + j33)];
			}
			/* Recursive loop 9 */
			/* Pre code */
			for (int j38 = 0; (j38 < 4); j38 = (j38 + 1)) {
				fRec21_tmp[j38] = fRec21_perm[j38];
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec21[i] = (fSlow9 + (0.999000013f * fRec21[(i - 1)]));
			}
			/* Post code */
			for (int j39 = 0; (j39 < 4); j39 = (j39 + 1)) {
				fRec21_perm[j39] = fRec21_tmp[(vsize + j39)];
			}
			/* Recursive loop 10 */
			/* Pre code */
			for (int j24 = 0; (j24 < 4); j24 = (j24 + 1)) {
				fRec5_tmp[j24] = fRec5_perm[j24];
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec5[i] = ((fRec6[i] + (0.999000013f * fRec5[(i - 1)])) - fRec6[(i - 1)]);
			}
			/* Post code */
			for (int j25 = 0; (j25 < 4); j25 = (j25 + 1)) {
				fRec5_perm[j25] = fRec5_tmp[(vsize + j25)];
			}
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec9[i] = std::tan((fConst2 * fRec21[i]));
			}
			/* Recursive loop 12 */
			/* Pre code */
			for (int j34 = 0; (j34 < 4); j34 = (j34 + 1)) {
				fRec15_tmp[j34] = fRec15_perm[j34];
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec15[i] = ((fRec16[i] + (0.999000013f * fRec15[(i - 1)])) - fRec16[(i - 1)]);
			}
			/* Post code */
			for (int j35 = 0; (j35 < 4); j35 = (j35 + 1)) {
				fRec15_perm[j35] = fRec15_tmp[(vsize + j35)];
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec3[i] = (3.14159274f * fRec4[i]);
			}
			/* Vectorizable loop 14 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec10[i] = (1.0f / fZec9[i]);
			}
			/* Recursive loop 15 */
			/* Pre code */
			for (int j36 = 0; (j36 < 4); j36 = (j36 + 1)) {
				fRec20_tmp[j36] = fRec20_perm[j36];
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec20[i] = (fSlow8 + (0.999000013f * fRec20[(i - 1)]));
			}
			/* Post code */
			for (int j37 = 0; (j37 < 4); j37 = (j37 + 1)) {
				fRec20_perm[j37] = fRec20_tmp[(vsize + j37)];
			}
			/* Vectorizable loop 16 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec4[i] = std::cos(fZec3[i]);
			}
			/* Vectorizable loop 17 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec5[i] = (fRec5[i] + fRec15[i]);
			}
			/* Vectorizable loop 18 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec6[i] = std::sin(fZec3[i]);
			}
			/* Recursive loop 19 */
			/* Pre code */
			for (int j2 = 0; (j2 < 4); j2 = (j2 + 1)) {
				fRec3_tmp[j2] = fRec3_perm[j2];
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec3[i] = (fSlow1 + (0.999000013f * fRec3[(i - 1)]));
			}
			/* Post code */
			for (int j3 = 0; (j3 < 4); j3 = (j3 + 1)) {
				fRec3_perm[j3] = fRec3_tmp[(vsize + j3)];
			}
			/* Vectorizable loop 20 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec8[i] = (fRec20[i] * ((fZec4[i] * (fRec5[i] - fRec15[i])) + (fZec6[i] * fZec5[i])));
			}
			/* Vectorizable loop 21 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec11[i] = (((fZec10[i] + -1.84775901f) / fZec9[i]) + 1.0f);
			}
			/* Vectorizable loop 22 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec12[i] = (1.0f - (1.0f / mydsp_faustpower2_f(fZec9[i])));
			}
			/* Vectorizable loop 23 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec13[i] = (((fZec10[i] + 1.84775901f) / fZec9[i]) + 1.0f);
			}
			/* Recursive loop 24 */
			/* Pre code */
			for (int j0 = 0; (j0 < 4); j0 = (j0 + 1)) {
				fRec2_tmp[j0] = fRec2_perm[j0];
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec2[i] = (fSlow0 + (0.999000013f * fRec2[(i - 1)]));
			}
			/* Post code */
			for (int j1 = 0; (j1 < 4); j1 = (j1 + 1)) {
				fRec2_perm[j1] = fRec2_tmp[(vsize + j1)];
			}
			/* Vectorizable loop 25 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec7[i] = ((fZec4[i] * fZec5[i]) + (fZec6[i] * (fRec15[i] - fRec5[i])));
			}
			/* Vectorizable loop 26 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec14[i] = (((fZec10[i] + -0.765366852f) / fZec9[i]) + 1.0f);
			}
			/* Vectorizable loop 27 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec15[i] = (((fZec10[i] + 0.765366852f) / fZec9[i]) + 1.0f);
			}
			/* Recursive loop 28 */
			/* Pre code */
			for (int j44 = 0; (j44 < 4); j44 = (j44 + 1)) {
				fRec23_tmp[j44] = fRec23_perm[j44];
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec23[i] = ((fRec2[i] * float(tanhf(float((0.25f * (fRec3[i] * (fZec7[i] - fZec8[i]))))))) - (((fZec11[i] * fRec23[(i - 2)]) + (2.0f * (fZec12[i] * fRec23[(i - 1)]))) / fZec13[i]));
			}
			/* Post code */
			for (int j45 = 0; (j45 < 4); j45 = (j45 + 1)) {
				fRec23_perm[j45] = fRec23_tmp[(vsize + j45)];
			}
			/* Recursive loop 29 */
			/* Pre code */
			for (int j40 = 0; (j40 < 4); j40 = (j40 + 1)) {
				fRec1_tmp[j40] = fRec1_perm[j40];
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec1[i] = ((fRec2[i] * float(tanhf(float((0.25f * (fRec3[i] * (fZec7[i] + fZec8[i]))))))) - (((fRec1[(i - 2)] * fZec11[i]) + (2.0f * (fRec1[(i - 1)] * fZec12[i]))) / fZec13[i]));
			}
			/* Post code */
			for (int j41 = 0; (j41 < 4); j41 = (j41 + 1)) {
				fRec1_perm[j41] = fRec1_tmp[(vsize + j41)];
			}
			/* Recursive loop 30 */
			/* Pre code */
			for (int j46 = 0; (j46 < 4); j46 = (j46 + 1)) {
				fRec22_tmp[j46] = fRec22_perm[j46];
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec22[i] = (((fRec23[(i - 2)] + (fRec23[i] + (2.0f * fRec23[(i - 1)]))) / fZec13[i]) - (((fZec14[i] * fRec22[(i - 2)]) + (2.0f * (fZec12[i] * fRec22[(i - 1)]))) / fZec15[i]));
			}
			/* Post code */
			for (int j47 = 0; (j47 < 4); j47 = (j47 + 1)) {
				fRec22_perm[j47] = fRec22_tmp[(vsize + j47)];
			}
			/* Recursive loop 31 */
			/* Pre code */
			for (int j42 = 0; (j42 < 4); j42 = (j42 + 1)) {
				fRec0_tmp[j42] = fRec0_perm[j42];
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec0[i] = (((fRec1[(i - 2)] + (fRec1[i] + (2.0f * fRec1[(i - 1)]))) / fZec13[i]) - (((fRec0[(i - 2)] * fZec14[i]) + (2.0f * (fZec12[i] * fRec0[(i - 1)]))) / fZec15[i]));
			}
			/* Post code */
			for (int j43 = 0; (j43 < 4); j43 = (j43 + 1)) {
				fRec0_perm[j43] = fRec0_tmp[(vsize + j43)];
			}
			/* Vectorizable loop 32 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				output1[i] = FAUSTFLOAT(((fRec22[(i - 2)] + (fRec22[i] + (2.0f * fRec22[(i - 1)]))) / fZec15[i]));
			}
			/* Vectorizable loop 33 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				output0[i] = FAUSTFLOAT(((fRec0[(i - 2)] + (fRec0[i] + (2.0f * fRec0[(i - 1)]))) / fZec15[i]));
			}
		}
	}

};

// END-FAUSTDSP

#endif
