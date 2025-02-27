/*
 * Copyright (C) 2011 Ericsson AB. All rights reserved.
 * Copyright (C) 2013 Apple Inc. All rights reserved.
 * Copyright (C) 2013 Nokia Corporation and/or its subsidiary(-ies).
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer
 *    in the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name of Ericsson nor the names of its contributors
 *    may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef UserMediaRequest_h
#define UserMediaRequest_h

#if ENABLE(MEDIA_STREAM)

#include "ActiveDOMObject.h"
#include "MediaDevices.h"
#include "MediaStreamCreationClient.h"
#include <wtf/PassRefPtr.h>
#include <wtf/RefCounted.h>
#include <wtf/text/WTFString.h>

namespace WebCore {

class Dictionary;
class Document;
class Frame;
class MediaConstraints;
class MediaStreamPrivate;
class NavigatorUserMediaErrorCallback;
class NavigatorUserMediaSuccessCallback;
class UserMediaController;
class SecurityOrigin;

typedef int ExceptionCode;

class UserMediaRequest : public MediaStreamCreationClient, public ContextDestructionObserver {
public:
    static void start(Document*, const Dictionary&, MediaDevices::Promise&&, ExceptionCode&);
    ~UserMediaRequest();

    WEBCORE_EXPORT SecurityOrigin* securityOrigin() const;

    void start();
    WEBCORE_EXPORT void userMediaAccessGranted();
    WEBCORE_EXPORT void userMediaAccessDenied();

    bool requiresAudio() const { return m_audioConstraints; }
    bool requiresVideo() const { return m_videoConstraints; }
    
    const Vector<String>& videoDeviceUIDs() const { return m_videoDeviceUIDs; }
    const Vector<String>& audioDeviceUIDs() const { return m_audioDeviceUIDs; }

    const Vector<String>& deviceUIDsVideo() const { return m_deviceUIDsVideo; }
    const Vector<String>& deviceUIDsAudio() const { return m_deviceUIDsAudio; }
private:
    UserMediaRequest(ScriptExecutionContext*, UserMediaController*, PassRefPtr<MediaConstraints> audioConstraints, PassRefPtr<MediaConstraints> videoConstraints, MediaDevices::Promise&&);

    // MediaStreamCreationClient
    virtual void constraintsValidated(const Vector<RefPtr<RealtimeMediaSource>>&, const Vector<RefPtr<RealtimeMediaSource>>&) override final;
    virtual void constraintsInvalid(const String& constraintName) override final;
    virtual void didCreateStream(PassRefPtr<MediaStreamPrivate>) override final;
    virtual void failedToCreateStreamWithConstraintsError(const String& constraintName) override final;
    virtual void failedToCreateStreamWithPermissionError() override final;

    // ContextDestructionObserver
    virtual void contextDestroyed() override final;
    
    RefPtr<MediaConstraints> m_audioConstraints;
    RefPtr<MediaConstraints> m_videoConstraints;
    
    Vector<String> m_deviceUIDsVideo;
    Vector<String> m_deviceUIDsAudio;

    Vector<String> m_videoDeviceUIDs;
    Vector<String> m_audioDeviceUIDs;
    
    UserMediaController* m_controller;

    MediaDevices::Promise m_promise;
};

} // namespace WebCore

#endif // ENABLE(MEDIA_STREAM)

#endif // UserMediaRequest_h
