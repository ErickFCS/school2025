import { useDispatch, useSelector } from 'react-redux';
import { State } from '../../store';
import { useMatch } from 'react-router-dom';
import { loadConfigsOfDevice } from '../../reducers/devices';
import { useEffect } from 'react';
import ConfigForm from '../ConfigForm';

const EditPage = () => {
    const match = useMatch("/edit/:device");
    const deviceId = Number(match?.params.device);
    const configs = useSelector((state: State) => (state.devices.configs))
    const dispatch = useDispatch()
    console.log("EditPage loaded");

    useEffect(() => {
        dispatch(loadConfigsOfDevice(deviceId));
    }, [dispatch, deviceId])

    return (
        <>
            {configs.map((e, i) => {
                console.log(e);
                return (
                    <ConfigForm key={`configForm${i}`} config={e} />
                );
            })}
        </>
    );
};

export default EditPage;
