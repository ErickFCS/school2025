import { loadAllDevices } from "../../reducers/devices";
import { State } from "../../store";
import LinkTo from "../LinkTo";
import LoadingSpinner from "../LoadingSpinner";
import { useEffect } from "react";
import Stack from "react-bootstrap/Stack";
import Table from "react-bootstrap/Table";
import { useDispatch, useSelector } from "react-redux";


const ListDevicesPage = () => {
    const dispatch = useDispatch();
    const devices = useSelector((state: State) => (state.devices));

    useEffect(() => {
        dispatch(loadAllDevices());
        const interval = setInterval(() => {
            dispatch(loadAllDevices());
        }, 10000);
        return (() => {
            clearInterval(interval);
        });
    }, [dispatch]);

    if (devices.loading) {
        return <LoadingSpinner />;
    }
    return (
        <Stack className="align-items-center">
            <Table style={{ marginTop: "10%", width: "50%" }} striped bordered>
                <thead>
                    <tr>
                        <th>ID</th>
                        <th>Start Time</th>
                    </tr>
                </thead>
                <tbody>
                    {devices.devices.map((e, i) => {
                        return (
                            <LinkTo to={`/info/${e.id}`} key={`link${i}`}>
                                <td key={`tdid${i}`}>{e.id}</td>
                                <td key={`tdtime${i}`}>{e.startTime}</td>
                            </LinkTo>
                        );
                    })}
                </tbody>
            </Table>
        </Stack>
    );
};

export default ListDevicesPage;
