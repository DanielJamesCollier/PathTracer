//
//  RenderGroup.h
//  PathTracer
//
//  Created by Daniel Collier on 24/01/2017.
//  Copyright © 2017 Daniel Collier. All rights reserved.
//

#ifndef Tracer_hpp
#define Tracer_hpp

#include <vector>
#include "Ray.hpp"

template<typename T>
class Tracable {
public:
    
};

template<typename T>
class TraceGroup {
public:
    TraceGroup();
    
    void addTracable(T const & traceObject) {
        m_traceGroup.push_back(traceObject);
    }
    
    void trace() {
        m_traceGroup.trace();
    }
    
private:
    std::vector<T> m_traceGroup;
};

#endif /* Tracer_hpp */
