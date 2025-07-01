import Button from "react-bootstrap/Button";
import { useDispatch, useSelector } from "react-redux";
import Table from "react-bootstrap/Table";
import { useMatch, useNavigate } from "react-router-dom";
import { State } from "../../store";
import { useEffect } from "react";
import { loadDataOfDevice } from "../../reducers/devices";
import LoadingSpinner from "../LoadingSpinner";


const InfoPage = () => {
    const match = useMatch("/info/:device");
    const deviceId = Number(match?.params.device);
    const navigate = useNavigate()
    const devices = useSelector((state: State) => (state.devices))
    const dispatch = useDispatch()

    useEffect(() => {
        dispatch(loadDataOfDevice(deviceId));
        const interval = setInterval(() => {
            dispatch(loadDataOfDevice(deviceId));
        }, 3000);
        return (() => {
            clearInterval(interval);
        });
    }, [dispatch, deviceId])

    const handleToEditConfig = () => {
        navigate(`/edit/${deviceId}`)
    }

    if (devices.loading) {
        return <LoadingSpinner />
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
                    {devices.data.map((data) => {
                        return (
                            <tr>
                                <td>{data.type}</td>
                                <td>{data.value}</td>
                                <td>{data.timestamp}</td>
                            </tr>
                        )
                    })}
                </tbody>
            </Table>
        </>
    );
};

export default InfoPage;
