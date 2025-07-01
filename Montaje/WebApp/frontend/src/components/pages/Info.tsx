import { loadDataOfDevice } from "../../reducers/devices";
import { State } from "../../store";
import LoadingSpinner from "../LoadingSpinner";
import { useEffect } from "react";
import Button from "react-bootstrap/Button";
import Table from "react-bootstrap/Table";
import { useDispatch, useSelector } from "react-redux";
import { useMatch, useNavigate } from "react-router-dom";


const InfoPage = () => {
    const match = useMatch("/info/:device");
    const deviceId = Number(match?.params.device);
    const navigate = useNavigate();
    const devices = useSelector((state: State) => (state.devices));
    const dispatch = useDispatch();

    useEffect(() => {
        dispatch(loadDataOfDevice(deviceId));
        const interval = setInterval(() => {
            dispatch(loadDataOfDevice(deviceId));
        }, 3000);
        return (() => {
            clearInterval(interval);
        });
    }, [dispatch, deviceId]);

    const handleToEditConfig = () => {
        navigate(`/edit/${deviceId}`);
    };

    if (devices.loading) {
        return <LoadingSpinner />;
    }

    return (
        <>
            <Button onClick={handleToEditConfig}>Edit Configuration</Button>
            <Table>
                <thead>
                    <tr>
                        <th>Type</th>
                        <th>Value</th>
                        <th>Timestamp</th>
                    </tr>
                </thead>
                <tbody>
                    {devices.data.map((data, i) => {
                        return (
                            <tr key={`date${i}`}>
                                <td>{data.type}</td>
                                <td>{data.value}</td>
                                <td>{data.timestamp}</td>
                            </tr>
                        );
                    })}
                </tbody>
            </Table>
        </>
    );
};

export default InfoPage;
