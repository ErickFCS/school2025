import { loadConfigsOfDevice } from "../../reducers/devices";
import { State } from "../../store";
import ConfigForm from "../ConfigForm";
import { useEffect } from "react";
import { useDispatch, useSelector } from "react-redux";
import { useMatch } from "react-router-dom";


const EditPage = () => {
    const match = useMatch("/edit/:device");
    const deviceId = Number(match?.params.device);
    const configs = useSelector((state: State) => (state.devices.configs));
    const dispatch = useDispatch();

    useEffect(() => {
        dispatch(loadConfigsOfDevice(deviceId));
    }, [dispatch, deviceId]);

    return (
        <>
            {configs.map((e, i) => {
                return (
                    <ConfigForm key={`configForm${i}`} config={e} espId={deviceId} />
                );
            })}
            <ConfigForm config={undefined} espId={deviceId}/>
        </>
    );
};

export default EditPage;
